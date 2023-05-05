using System.Collections;
using UnityEngine;

public class RandomColor : MonoBehaviour
{
    public Color ColorCurrent;
    public float Time;
    public Renderer RendererCurrent;

    private void Start()
    {
        StartCoroutine(ChangeShaderColor()) ;
    }

    IEnumerator ChangeShaderColor()
    {
        while (true)
        {
            ColorCurrent = Random.ColorHSV();
            RendererCurrent.material.SetColor("_Color", ColorCurrent);
            yield return new WaitForSeconds(Time);
        }
    }
}
