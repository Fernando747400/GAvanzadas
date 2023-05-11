Shader "Unlit/Parallax"
{
    Properties{
        _MainTex("Albedo", 2D) = "white" {}
        _HeightMap("Height Map", 2D) = "white" {}
        _NormalMap("Normal Map", 2D) = "bump" {}
        _ParallaxStrength("Parallax Strength", Range(0, 1)) = 0.1
        _HeightMapStrength("Height Map Strength", Range(0, 1)) = 0.1
        _NormalMapStrength("Normal Map Strength", Range(0, 1)) = 0.1
    }

        SubShader{
            Tags { "RenderType" = "Opaque" }
            LOD 200

            CGPROGRAM
            #pragma surface surf Lambert

            sampler2D _MainTex;
            sampler2D _HeightMap;
            sampler2D _NormalMap;
            float _ParallaxStrength;
            float _HeightMapStrength;
            float _NormalMapStrength;

            struct Input {
                float2 uv_MainTex;
                float2 uv_HeightMap;
                float3 worldPos;
            };

            void surf(Input IN, inout SurfaceOutput o) {
                // Tangent space calculations
                float3 worldNormal = UnpackNormal(tex2D(_NormalMap, IN.uv_MainTex)) * _NormalMapStrength;
                float3 worldTangent = cross(worldNormal, float3(0, 0, 1));
                float3 worldBinormal = cross(worldNormal, worldTangent);

                // View direction calculations
                float3 viewDir = normalize(_WorldSpaceCameraPos - IN.worldPos);
                float3 viewDirTangent = float3(dot(viewDir, worldTangent), dot(viewDir, worldBinormal), dot(viewDir, worldNormal));

                // Height and parallax offset calculations
                float height = tex2D(_HeightMap, IN.uv_HeightMap).r * _HeightMapStrength;
                float2 parallaxOffset = height * _ParallaxStrength * viewDirTangent.xy;
                float2 finalUV = IN.uv_MainTex + parallaxOffset;

                // Final texture color
                o.Albedo = tex2D(_MainTex, finalUV).rgb;
                o.Alpha = 1.0;
            }
            ENDCG
        }
            FallBack "Diffuse"
}
