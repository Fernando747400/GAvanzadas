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

            // Compute the tangent to world matrix
            float3x3 ComputeTangentToWorldMatrix(float3 normal, float3 tangent)
            {
                float3 binormal = cross(normal, tangent);
                return float3x3(tangent, binormal, normal);
            }

            struct Input {
                float2 uv_MainTex;
                float2 uv_HeightMap;
                float3 worldPos;
            };

            void surf(Input IN, inout SurfaceOutput o) {

                // Unpack the normal map
                float3 worldNormal = UnpackNormal(tex2D(_NormalMap, IN.uv_MainTex)) * _NormalMapStrength;

                // Compute the tangent and tangent to world matrix
                float3 worldTangent = cross(worldNormal, float3(0, 0, 1));
                float3x3 tangentToWorld = ComputeTangentToWorldMatrix(worldNormal, worldTangent);

                // Transform view direction to tangent space
                float3 viewDir = normalize(_WorldSpaceCameraPos - IN.worldPos);
                float3 viewDirTangent = mul(tangentToWorld, viewDir);

                // Calculate height and parallax offset
                float height = tex2D(_HeightMap, IN.uv_HeightMap).r * _HeightMapStrength;
                float2 parallaxOffset = height * _ParallaxStrength * viewDirTangent.xy;
                float2 finalUV = IN.uv_MainTex + parallaxOffset;

                // Sample the main texture
                o.Albedo = tex2D(_MainTex, finalUV).rgb;
                o.Alpha = 1.0;
            }
            ENDCG
       }

           // Fallback to diffuse shader
                FallBack "Diffuse"
}

