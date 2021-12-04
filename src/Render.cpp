
#include "Render.h"






namespace Render
{
	real windowWidth = 800;
	real windowHeight = 600;
	GLFWwindow* renderWindow;
	Shader defaultShader;
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 identity = glm::mat4(1.0f);
	std::vector<std::unique_ptr<Primitive>> primitives;
	

	void initialize()
	{
		

		// Initialize GLFW
		glfwInit();

		// Tell GLFW what version of OpenGL we are using 
		// In this case we are using OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Tell GLFW we are using the CORE profile
		// So that means we only have the modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		// Create a GLFWwindow object of windowWidth by windowWidthv pixels, naming it "RenderWindow"
		renderWindow = glfwCreateWindow(windowWidth, windowHeight, "RenderWindow", NULL, NULL);
		// Error check if the window fails to create
		if (renderWindow == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();

		}
		// Introduce the window into the current context
		glfwMakeContextCurrent(renderWindow);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = windowWidth, y = windowHeight
		glViewport(0, 0, windowWidth, windowHeight);

		
		
		//Load default Shader
		defaultShader = Shader("resources/default.vert", "resources/default.frag");
		projection = glm::ortho(0.0f, Render::windowWidth, Render::windowHeight, 0.0f, -1.0f, 1.0f);
		
		defaultShader.makeCurrentShader();

		primitives.push_back(std::make_unique<Primitive>(PrimitiveType::Circle));
		primitives.push_back(std::make_unique<Primitive>(PrimitiveType::Rectangle));

	}

	void terminate()
	{
		defaultShader.terminate();
		// Delete window before ending the program
		glfwDestroyWindow(renderWindow);
		// Terminate GLFW before ending the program
		glfwTerminate();
	}

	void changeWindowSize(real width, real height)
	{
		windowWidth = width;
		windowHeight = height;
		projection = glm::ortho(0.0f, Render::windowWidth, Render::windowHeight, 0.0f, -1.0f, 1.0f);
		glfwSetWindowSize(renderWindow, windowWidth, windowHeight);
	}

	void Render::renderBody(RigidBody* body)
	{
		//For now only translation is taken into account when rendering
		if (body->shape->type == ShapeType::Circle)
		{
			drawPrimitive(primitives[0].get(), body->position, body->angle,body->shape->radius, body->shape->radius);
			
		}
		else if (body->shape->type == ShapeType::AABB)
		{
			drawPrimitive(primitives[1].get(), body->position, body->angle, body->shape->width, body->shape->height);
			
		}
		else
		{
			//int	projectionLoc = glGetUniformLocation(defaultShader.reference, "projection");

			//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
			//const glm::mat4 yow;
			std::string teyst = "projection";
			
			defaultShader.setUniform("projection", projection);



			model = glm::translate(identity, glm::vec3(body->position, 0.0f));
			model = glm::rotate(model, glm::radians(body->angle), glm::vec3(0.0f, 0.0f, 1.0f));
			//int modelLoc = glGetUniformLocation(defaultShader.reference, "model");

			//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			defaultShader.setUniform("model", model);

			glBindVertexArray(body->vao);
			glDrawElements(GL_LINE_STRIP, body->shape->nbPoints, GL_UNSIGNED_INT, 0);


			if (COM_FLAG && body->shape->type == ShapeType::Polygon)
			{

				glBindVertexArray(body->COMvao);
				glDrawArrays(GL_POINTS, 0, 1);


			}
		}
		

		//body->render();

	}


	void setNewMouseButtonCallBack(GLFWmousebuttonfun callback)
	{
		glfwSetMouseButtonCallback(renderWindow,callback);
	}

	void drawPrimitive(Primitive* primitive, glm::vec2 position, float angle, float xScale,float yScale)
	{
		
		defaultShader.makeCurrentShader();
		//int	projectionLoc = glGetUniformLocation(defaultShader.reference, "projection");
		//int	projectionLoc = glGetUniformLocation(myShader.ID, "projection");
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		defaultShader.setUniform("projection",projection);


		model = glm::translate(identity, glm::vec3(position, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(xScale, yScale, 1));
		//int modelLoc = glGetUniformLocation(defaultShader.reference, "model");

		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		defaultShader.setUniform("model", model);

		/*primitive->useWireFrameVAO();
		
		glDrawElements(GL_LINE_STRIP, primitive->nbPoints, GL_UNSIGNED_INT, 0);*/

		primitive->drawSolid();
		//primitive->drawWireFrame();
		//glDrawElements(GL_TRIANGLES, , GL_UNSIGNED_INT, 0);


		/*if (COM_FLAG && body->shape->type == ShapeType::Polygon)
		{

			glBindVertexArray(body->COMvao);
			glDrawArrays(GL_POINTS, 0, 1);


		}*/

		//body->render();

	}

}




