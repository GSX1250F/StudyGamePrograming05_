// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// 頂点シェーダーからのテクスチャ座標入力
in vec2 fragTexCoord;

// 出力色
out vec4 outColor;

// テクスチャサンプリング用
uniform sampler2D uTexture;

void main()
{
	// テクスチャから色をサンプリングする
	outColor = texture(uTexture, fragTexCoord);
}
