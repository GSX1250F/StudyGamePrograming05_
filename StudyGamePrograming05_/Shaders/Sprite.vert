// Request GLSL 3.3
#version 330

// ワールド変換とビュー射影のためのuniform行列
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// 属性0は位置、属性1はテクスチャ座標
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

// 出力にテクスチャ座標を追加
out vec2 fragTexCoord;

void main()
{
	// 位置座標を同次座標系に変換
	vec4 pos = vec4(inPosition, 1.0);
	// 位置をワールド空間に、そしてクリップ空間に変換
	gl_Position = pos * uWorldTransform * uViewProj;

	// テクスチャ座標をフラグメントシェーダーに渡す
	fragTexCoord = inTexCoord;
}
