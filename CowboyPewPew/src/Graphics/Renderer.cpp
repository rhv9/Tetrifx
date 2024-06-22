#include <pch.h>
#include "Renderer.h"
#include <glad/glad.h>
#include "VertexArray.h"

static struct RenderData
{
    VertexArray quadVA;
};

static RenderData renderData;

void Renderer::Init()
{
    float vertices[] = {
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0 
    };

    VertexDataMap vertexDatas = {
        { "aPos", 3, VertexDataType::Float, VertexDataBool::False}
    };

    LOG_CORE_TRACE("Renderer::Init()");

    renderData.quadVA = VertexArray::Create(vertexDatas, vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));

}

void Renderer::StartScene(glm::mat4 camera)
{
    glClearColor(1.00f, 0.49f, 0.04f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DrawQuad()
{
    renderData.quadVA.Bind();
	glDrawElements(GL_TRIANGLES, renderData.quadVA.GetIndicesCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::EndScene()
{
}
