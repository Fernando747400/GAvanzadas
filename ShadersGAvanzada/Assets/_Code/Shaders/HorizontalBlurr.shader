Shader "Unlit/HorizontalBlurr"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _KernelSize("Kernel Size", Range(1,30)) = 5
        _TextureWidth("Texture Width",Range (1,4096)) = 1024
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
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
            float4 _TextureWidth;

            v2f vertex (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            fixed4 fragVertical(v2f i) : SV_Target
            {
               float texelSize = 1.0 / _TextureWidth;
               fixed4 result = fixed4(0.0, 0.0, 0.0, 0.0);

               for (int j = -_KernelSize; j <= _KernelSize; j++) 
               {
                   float weight = float(j);
                   fixed4 sample = text2D(_MainTex, i.uv + fixed2(weight * texelSize, 0.0));
                   result += sample;
               }

               result /= _KernelSize * 2 + 1;
               return result;
            }
            ENDCG
        }
    }
}
