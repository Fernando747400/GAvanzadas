Shader "Unlit/VerticalBlur"
{
    Properties
    {
        _MainTex("Texture", 2D) = "white" {}
        _KernelSize("Kernel Size", Range(1,100)) = 5
        _TextureHeight("Texture Height", Range(1, 4096)) = 1024
    }

        SubShader
        {
            Tags { "RenderType" = "Opaque" }
            LOD 100

            Pass
            {
                CGPROGRAM
                #pragma vertex vertex
                #pragma fragment fragVertical

                #include "UnityCG.cginc"

                struct appdata
                {
                    float4 vertex : POSITION;
                    float2 uv : TEXCOORD0;
                };

                struct v2f
                {
                    float2 uv : TEXCOORD0;
                    float4 vertex : SV_POSITION;
                };

                sampler2D _MainTex;
                float _KernelSize;
                float _TextureHeight;

                v2f vertex(appdata v)
                {
                    v2f o;
                    o.vertex = UnityObjectToClipPos(v.vertex);
                    o.uv = v.uv;
                    return o;
                }

                fixed4 fragVertical(v2f i) : SV_Target
                {
                    float texelSize = 1.0 / _TextureHeight;
                    fixed4 result = tex2D(_MainTex, i.uv);

                    if (_KernelSize > 1) {
                        float sigma = _KernelSize / 3.0;
                        float totalWeight = 0.0;
                        float4 blur = fixed4(0.0, 0.0, 0.0, 0.0);

                        for (int j = -_KernelSize; j <= _KernelSize; j++)
                        {
                            float weight = exp(-j * j / (2 * sigma * sigma));
                            totalWeight += weight;
                            fixed4 sample = tex2D(_MainTex, i.uv + fixed2(0.0, j * texelSize));
                            blur += sample * weight;
                        }

                        result = blur / totalWeight;
                    }

                    return result;
                }
                ENDCG
            }
        }
}

