
#include "Scene.h"
#include "Camera.h"
#include "FileReader.h"
#include "Renderer.h"


int main(int argc, char* argv[])
{
	std::string filename;
	const int file_count = 7;
	std::string files[file_count] = {
		"scene4-ambient.test", 
		"scene4-diffuse.test",
		"scene4-emission.test",
		"scene4-specular.test",
		"scene5.test",
		"scene6.test",
		"scene7.test"
	};

	Renderer* renderer = new Renderer();
	for (int i = 0; i < file_count; i++)
	{
		std::cout << files[i] << std::endl;
		renderer->SceneRendering(files[i]);
		std::cout << "Finished: " << files[i] << " , filename: " << renderer->m_Scene->output_filename << std::endl;
	}
	



	delete renderer;

	return 0;
}