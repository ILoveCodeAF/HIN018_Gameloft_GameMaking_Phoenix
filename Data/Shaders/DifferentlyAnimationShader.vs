#define MAX_NUM_VERTICES 128

attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;

uniform 	mat4 	u_matMVP;
uniform 	mat4 	u_matWorld;
uniform 	float 	u_alpha;

uniform		int	u_numFrames;
uniform		int	u_currentFrame;
uniform		float	u_vertices_x0[MAX_NUM_VERTICES];
uniform		float	u_vertices_x1[MAX_NUM_VERTICES];
uniform		float	u_vertices_y0[MAX_NUM_VERTICES];
uniform		float	u_vertices_y1[MAX_NUM_VERTICES];

varying 	vec2 	v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_matMVP * posL;
	if (int(a_uv.x) == 0 && int(a_uv.y) == 0) 
	{
		v_uv = vec2(u_vertices_x0[u_currentFrame], u_vertices_y0[u_currentFrame]);
	}
	if (int(a_uv.x) == 1 && int(a_uv.y) == 0) 
	{
		v_uv = vec2(u_vertices_x1[u_currentFrame], u_vertices_y0[u_currentFrame]);
	}
	if (int(a_uv.x) == 0 && int(a_uv.y) == 1) 
	{
		v_uv = vec2(u_vertices_x0[u_currentFrame], u_vertices_y1[u_currentFrame]);
	}
	if (int(a_uv.x) == 1 && int(a_uv.y) == 1) 
	{
		v_uv = vec2(u_vertices_x1[u_currentFrame], u_vertices_y1[u_currentFrame]);
	}

}
   