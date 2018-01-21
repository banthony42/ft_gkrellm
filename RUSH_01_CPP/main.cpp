





#include "Window.hpp"
#include "Renderer.hpp"
#include "AGraphical.hpp"
#include "NCURSESGraphical.hpp"

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	AGraphical *graph;
	if (argc > 1 && argv[1][0] == 'n')
	{
		// graph = new NCURSESGraphical();
		return (0);
	}
	else
		graph = new Renderer();
	while (graph->isOpen())
	{
		graph->updateVisual();
		graph->refreshVisual();
	}
	delete graph;
	return (0);
}
