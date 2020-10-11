
struct v2f
{
    float4 color : Color;
    float4 position : SV_Position;
};

float4 main(v2f i) : SV_Target
{
    return i.color;
}