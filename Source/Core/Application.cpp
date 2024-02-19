#include "epch.h"
#include "Application.h"
#include "Window.h"
#include "Utility/Time.h"
#include "Renderer/Renderer3D.h"
#include "Renderer/RenderingCommand.h"


UApplication* UApplication::sInstance = nullptr;

UApplication::UApplication()
{
	ASSERT(sInstance == nullptr, "Only one instance of UApplication can exist at a time!");

	sInstance = this;
	bRunning = false;
}

UApplication::~UApplication()
{

}

void UApplication::Initialize()
{
	ULog::Initialize();
	URenderingCommand::Initialize();

	TimeHandle = std::make_shared<UTime>();

	FWindowProps props;
	props.Width = 1000;
	props.Height = 800;
	props.Title = "App";
	GameWindow = std::make_shared<UWindow>(props);

	//Renderer2D = std::make_shared<URenderer2D>(); // !TODO: include renderer2D
	Renderer3D = std::make_shared<URenderer3D>();
}

void UApplication::Run()
{
	bRunning = true;

	// Main game loop
	while (bRunning)
	{
		TimeHandle->OnUpdate();
		float deltaTime = TimeHandle->GetDeltaTime();

		GameWindow->OnUpdate(deltaTime);
		//Renderer2D->OnUpdate(deltaTime);
		Renderer3D->RenderSphere();
	}
}

void UApplication::WindowClosed()
{
	if (GameWindow->IsRunning()) return;

	bRunning = false;
}


int main()
{
	UApplication a;
	a.Initialize();
	a.Run();

	return 0;
}