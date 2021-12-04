
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>


#include <imgui.h>
#include <imgui_impl_glfw.h>



#include <imgui_impl_opengl3.h>





#include "RigidBody.h"
#include "Render.h"
#include "Collision.h"
#include "timeOperations.h"
#include "PhysicProcess.h"

#include "Debug.h"
#include "Bone.h"





//On choisi un dt de 16ms (1/60fps)

std::chrono::nanoseconds accumulator(0ns);

// Vector that contains all of our physical objects
//std::vector<std::unique_ptr<RigidBody>> bodies;




void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	
	double mouseX;
	double mouseY;

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		
		
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		
		
	}
}


int main()
{
	
	std::cout.setf(std::ios::fixed);

	Render::initialize();
	Debug::initialize();
	
	GLFWwindow* window = Render::renderWindow;
	Shader defaultShader = Render::defaultShader;

	Primitive testP(PrimitiveType::Rectangle);
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	//const char* glslVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	const char* version = "#version 130";
	//std::cout << "the returned version is : " << (char*)glad_glGetString(GL_VERSION) << "\n";
	ImGui_ImplOpenGL3_Init(version);
	//ImGui_ImplOpenGL3_Init((char*)glad_glGetString(GL_SHADING_LANGUAGE_VERSION));
	//ImGui_ImplOpenGL3_Init("#130");
	
	

	
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glPointSize(2);

	

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	
	using clock = std::chrono::high_resolution_clock;
	auto frameStart = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	

	Bone bone = { 50,0,glm::vec2(400,300) };
	//glLineWidth(10);

	static double mouseX = 0;
	static double mouseY = 0;
	// Main while loop
	

	glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(window))
	{
		
		currentTime = std::chrono::high_resolution_clock::now();
		// Store the time elapsed since the last frame began
		accumulator += currentTime - frameStart;

		// Record the starting of this frame
		frameStart = currentTime;


		if (accumulator > std::chrono::microseconds(200ms))
		{
			accumulator = std::chrono::microseconds(200ms);
		}

		while (accumulator > dt)
		{
			
			
			glfwGetCursorPos(window, &mouseX, &mouseY);

			
			setAngle(mouseX, mouseY, &bone);

			
			accumulator -= dt;
		}

		//We calculate the alpha for possible interpolation (not implemented yet)
		auto alpha = (float)accumulator.count() / dt.count();



		// Render part
		// Specify the color of the background
		glClearColor(clear_color.x,clear_color.y,clear_color.z,clear_color.w);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		

		
		
		
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text yowowowowo.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		//if (ImGui::Button("Yow"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);
		ImGui::Text("Mouse X : %g", mouseX);
		ImGui::Text("Mouse Y : %g", mouseY);
		ImGui::Text("Mouse Angle : %g", atan2(mouseY-300,mouseX-400));

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
		
		Debug::drawDebugLine(glm::vec3(bone.position,0), bone.length, bone.angle);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	//Shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	Render::terminate();
	
	return 0;
}


