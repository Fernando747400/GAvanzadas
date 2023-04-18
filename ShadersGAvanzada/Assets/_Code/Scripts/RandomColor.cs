using System.Collections;
using Unity.VisualScripting;
using UnityEngine;

public class RandomColor : MonoBehaviour
{
    public Color color;
    public float time;
    public Renderer renderer;

    private void Start()
    {
        StartCoroutine(ChangeShaderColor()) ;
    }

    IEnumerator ChangeShaderColor()
    {
        while (true)
        {
            color = Random.ColorHSV();
            renderer.material.SetColor("_Color", color);
            yield return new WaitForSeconds(time);
        }
    }
}
