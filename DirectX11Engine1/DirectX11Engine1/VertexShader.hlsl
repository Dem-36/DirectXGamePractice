struct appdata
{
    float2 vertex : Position;
    float3 color : Color;
};

struct v2f
{
    float3 color : Color;
    //SV_Position�̃Z�}���e�B�N�X���g�p�����ꍇ�A
    //�^��float4�łȂ��Ă͂����Ȃ�
    float4 position : SV_Position;
};

v2f main(appdata v)
{
    v2f o;
    o.position = float4(v.vertex.x, v.vertex.y, 0.0f, 1.0f);
    o.color = v.color;
    return o;
}