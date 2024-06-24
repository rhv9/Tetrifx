#include <pch.h>
#include "Renderer.h"
#include <glad/glad.h>
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

static struct RenderData
{
    VertexArray quadVA;
    Ref<Shader> shaderQuad;

    Ref<Texture> texture;
};

static RenderData renderData;

void Renderer::Init()
{
    LOG_CORE_INFO("Renderer::Init()");

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderData.shaderQuad = CreateRef<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

    float vertices[] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0 
    };

    VertexDataMap vertexDatas = {
        { "aPos", 3, VertexDataType::Float, VertexDataBool::False},
        { "aTexCoord", 2, VertexDataType::Float, VertexDataBool::False},
    };

    renderData.quadVA = VertexArray::Create(vertexDatas, vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));

    renderData.texture = std::make_unique<Texture>("assets/textures/spritesheet.png");

    renderData.texture->Bind(0);
}

void Renderer::StartScene(const Camera& camera)
{
    renderData.shaderQuad->UniformMat4("u_ViewProjectionMatrix", camera.GetProjection());

    glClearColor(1.00f, 0.49f, 0.04f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& scale)
{
    renderData.shaderQuad->Use();

    glm::mat4 transform = glm::scale(glm::identity<glm::mat4>(), { scale, 1.0f }) * glm::translate(glm::identity<glm::mat4>(), position);

    renderData.shaderQuad->UniformMat4("u_Transform", transform);
    renderData.shaderQuad->UniformInt("uTextureSampler", 0);

    renderData.quadVA.Bind();

    renderData.texture->Bind(0);
	glDrawElements(GL_TRIANGLES, renderData.quadVA.GetIndicesCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::EndScene()
{
}
