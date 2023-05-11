Shader "Unlit/Disolve"
{
    Properties{
           _MainTex("Main Texture", 2D) = "white" {}
           _NoiseTex("Noise Texture", 2D) = "white" {}
           _DissolveSpeed("Dissolve Speed", Range(0.1, 10.0)) = 1.0
    }

        SubShader{
            Tags { "Queue" = "Transparent" "RenderType" = "Opaque" }
            LOD 100

            Pass {
                CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag
                #include "UnityCG.cginc"

                struct appdata {
                    float4 vertex : POSITION;
                    float2 uv : TEXCOORD0;
                };

                struct v2f {
                    float2 uv : TEXCOORD0;
                    float4 vertex : SV_POSITION;
                };

                sampler2D _MainTex;
                sampler2D _NoiseTex;
                float _DissolveSpeed;

                v2f vert(appdata v) {
                    v2f o;
                    o.vertex = UnityObjectToClipPos(v.vertex);
                    o.uv = v.uv;
                    return o;
                }

                fixed4 frag(v2f i) : SV_Target {
                    float4 mainTex = tex2D(_MainTex, i.uv);
                    float4 noiseTex = tex2D(_NoiseTex, i.uv);

                    float noiseValue = noiseTex.r;

                    float dissolveThreshold = smoothstep(0.0, 1.0, frac(_Time.y * _DissolveSpeed));

                    if (noiseValue < dissolveThreshold || noiseValue >(1.0 - dissolveThreshold)) {
                        discard;
                    }

                    float dissolveAmount = 1.0 - smoothstep(dissolveThreshold, 1.0 - dissolveThreshold, noiseValue);
                    float4 dissolveColor = mainTex;

                    #if UNITY_TEXTURE_ALIASED
                    // Texture filtering is disabled for some platforms, no need to lerp
                #else
                    // Avoid lerp with the same arguments
                    if (dissolveAmount != 0.0) {
                        dissolveColor = lerp(mainTex, mainTex, dissolveAmount);
                    }
                #endif

                    return dissolveColor;
                }
                ENDCG
            }
        }
               Fallback "Diffuse"
}
