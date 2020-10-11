
struct v2f
{
    float3 color : Color;
    float4 position : SV_Position;
};

float4 main(v2f i) : SV_Target
{
    return float4(i.color, 1.0f);
}