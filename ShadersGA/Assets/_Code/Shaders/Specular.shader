Shader "Unlit/Specular"
{
    Properties{
     _MainTex("Texture", 2D) = "white" {}
     _ReflMap("Reflection Map", 2D) = "white" {}

     _Specular("Specular Power", Range(1, 256)) = 64
     _Metallic("Metallic", Range(0,1)) = 0
     _Smoothness("Smoothness", Range(0,1)) = 0.5
    }

        SubShader{
            LOD 100

            Tags {"Queue" = "Transparent" "RenderType" = "Opaque"}

            CGPROGRAM
            #pragma surface surf Standard

            sampler2D _MainTex;
            sampler2D _ReflMap;
            float _Specular;
            float _Metallic;
            float _Smoothness;

            struct Input {
                float2 uv_MainTex;
                float2 uv_ReflMap;
                float3 worldPos;
                float3 worldNormal;
                float3 worldViewDir;
            };

            void surf(Input IN, inout SurfaceOutputStandard o) {
                float3 worldLightDir = normalize(_WorldSpaceLightPos0.xyz);
                float3 worldViewDir = normalize(IN.worldViewDir);
                float3 worldHalfDir = normalize(worldLightDir + worldViewDir);
                float NdotH = saturate(dot(IN.worldNormal, worldHalfDir));
                float specular = pow(NdotH, _Specular);
                float3 reflMapColor = tex2D(_ReflMap, IN.uv_ReflMap).rgb;
                float reflIntensity = 1.0 - (reflMapColor.r + reflMapColor.g + reflMapColor.b) / 3.0;
                o.Emission = reflIntensity * specular;
                o.Metallic = _Metallic;
                o.Smoothness = _Smoothness;
                o.Albedo = tex2D(_MainTex, IN.uv_MainTex).rgb;
            }
            ENDCG
     }

         FallBack "Diffuse"
}
