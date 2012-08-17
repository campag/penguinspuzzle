/*
This file contains the functions to create and use shaders.
*/

#include <stdio.h>
#include "global.h"
#include "shaders.h"

/*
Print out the compile log for a shader
*/
static void showlog(GLint shader)
{
   // Prints the compile log for a shader
   char log[1024];
   glGetShaderInfoLog(shader,sizeof log,NULL,log);
   printf("%d:shader:\n%s\n", shader, log);
}

/*
Print out the link log for a program
*/
static void showprogramlog(GLint shader)
{
   // Prints the information log for a program object
   char log[1024];
   glGetProgramInfoLog(shader,sizeof log,NULL,log);
   printf("%d:program:\n%s\n", shader, log);
}

/*
Creates and compiles a new shader.

<shader_src> is a text string containing the source for the shader.
<is_frag> should be 1 for fragment shaders, or 0 for vertex shaders.
*/
int getShader(const GLchar *shader_src,int is_frag) 
{
	int shader = glCreateShader(is_frag ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER);
	
	glShaderSource(shader, 1, &shader_src, 0);
	glCompileShader(shader);

	//if (!glGetShaderParameter(shader, GL_COMPILE_STATUS))
	//showlog(shader);

	return shader;
}


/* Creates a shader object with the given vertex and fragment shaders */
SHADER_T *shader_new(const GLchar *vs, const GLchar *fs) 
{
	SHADER_T *s;
	NEW(s);
    int fragmentShader = getShader(fs,1);
    int vertexShader = getShader(vs,0);

    int program = glCreateProgram();
	s->program = program; 
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    //if (!glGetProgramParameter(program, GL_LINK_STATUS)) 
	//showprogramlog(program);

	s->attr_tex             = glGetAttribLocation(program, "tex");
	s->attr_vertex          = glGetAttribLocation(program, "vertex");
	s->attr_normal          = glGetAttribLocation(program, "normal");
	s->unif_world           = glGetUniformLocation(program, "world");
	s->unif_view            = glGetUniformLocation(program, "view");
	s->unif_view_reflect    = glGetUniformLocation(program, "view_reflect");
	s->unif_color           = glGetUniformLocation(program, "color");
	s->unif_texture         = glGetUniformLocation(program, "texture");
	s->unif_texture_reflect = glGetUniformLocation(program, "texture_reflect");
	s->unif_blend           = glGetUniformLocation(program, "blend");
    return s;
}

/*
Make this shaders program active
*/
void shader_select(SHADER_T *s)
{
	assert(s);
	glUseProgram ( s->program );

	glUniform1i(s->unif_texture, 0);
	glUniform1i(s->unif_texture_reflect, 1);
	shader_blend(s,0.0,0.0,0.0,0.0);
}

/* 
Configure the blending equations (some variables used in some of the shaders)
*/
void shader_blend(SHADER_T *s,float bx,float by,float bz,float bw)
{
	assert(s);
	glUniform4f(s->unif_blend, bx, by, bz, bw);
}

/*
Configure the world matrix
*/	
void shader_world(SHADER_T *s, float M[4][4])
{
	glUniformMatrix4fv(s->unif_world,16,GL_FALSE,(float*)M); // Note that Raspberry Pi does not support the input of transposed matrices
}

/*
Configure the view matrix
*/	
void shader_view(SHADER_T *s, float M[4][4])
{
	glUniformMatrix4fv(s->unif_view,16,GL_FALSE,(float*)M); // Note that Raspberry Pi does not support the input of transposed matrices
}

/*
Configure the reflected view matrix
*/	
void shader_view2(SHADER_T *s, float M[4][4])
{
	glUniformMatrix4fv(s->unif_view_reflect,16,GL_FALSE,(float*)M); // Note that Raspberry Pi does not support the input of transposed matrices
}

