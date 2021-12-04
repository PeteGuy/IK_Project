#include "Debug.h"
#include "Render.h"



namespace Debug
{

	GLfloat baseLine[] =
	{
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f
	};

	unsigned int lineVBO;
	unsigned int lineVAO;

	void initialize()
	{
		glGenVertexArrays(1, &lineVAO);
		glGenBuffers(1, &lineVBO);


		glBindVertexArray(lineVAO);
		glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
		//glBufferData(GL_ARRAY_BUFFER, shape->points.size() * sizeof(real), shape->points.data(), GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(baseLine), baseLine, GL_STATIC_DRAW);





		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real), (void*)0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


	}

	void drawDebugLine(glm::vec3 position, float length, float angle)
	{
		glm::mat4 identity = glm::mat4(1.0f);
		Render::defaultShader.makeCurrentShader();


		//Render::defaultShader.SetUniform("projection", Render::defaultCamera.GetProjMatrix());
		int	projectionLoc = glGetUniformLocation(Render::defaultShader.reference, "projection");
		//int	projectionLoc = glGetUniformLocation(myShader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(Render::projection));



		//Render::defaultShader.SetUniform("view", Render::defaultCamera.GetViewMatrix());

		glm::mat4 model = glm::translate(identity, position);
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(length));

		//Render::defaultShader.SetUniform("model", model);

		int modelLoc = glGetUniformLocation(Render::defaultShader.reference, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(lineVAO);

		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
		//glDrawElements(GL_LINE_STRIP, body->shape->nbPoints, GL_UNSIGNED_INT, 0);
	}

	void drawDebugLine(glm::vec2 pos1, glm::vec2 pos2)
	{
		glm::vec2 v = pos2 - pos1;

		float angle;
		float length;


		length = glm::length(v);

		angle = atan2(v.y, v.x);
		//std::cout << "angle : " << angle << "\n";


		drawDebugLine(glm::vec3(pos1, 0), length, angle);
	}

	void drawDebugVector(glm::vec2 origin, glm::vec2 v)
	{
		drawDebugLine(origin, origin + v);
	}



	float getVectorAngle()
	{

		return 1.0f;
	}


	void log(const char* varname, glm::vec2 vec)
	{
		std::cout << varname << " : (" << vec.x << "," << vec.y << ")" << "\n";
	}
	void log(const char* varname, int entier)
	{
		//string x = NAME_OF(entier);
		std::cout << varname << " : " << entier << "\n";
	}
	void log(const char* varname, float flottant)
	{
		std::cout << varname << " : " << flottant << "\n";
	}

	void log(const char* texte)
	{
		std::cout << texte << "\n";
	}
}
