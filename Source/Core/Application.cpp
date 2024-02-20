#include "epch.h"
#include "Application.h"
#include "Window.h"
#include "Utility/Time.h"
#include "Renderer/Renderer3D.h"
#include "Renderer/RenderingCommand.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


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
	props.Title = "Planet Generator";
	GameWindow = std::make_shared<UWindow>(props);

	//Renderer2D = std::make_shared<URenderer2D>(); // !TODO: include renderer2D
	Renderer3D = std::make_shared<URenderer3D>();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	float fontSize = 50.0f;
	io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/fonts/arial.ttf", fontSize);

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)GetWindow()->GetNativeWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

void UApplication::Run()
{
	bRunning = true;

	// .ImGui variables
	bool bWireframe = false;

	// Main game loop
	while (bRunning)
	{
		TimeHandle->OnUpdate();
		float deltaTime = TimeHandle->GetDeltaTime();

		GameWindow->OnUpdate(deltaTime);
		//Renderer2D->OnUpdate(deltaTime);
		Renderer3D->RenderSphere();


		// .ImGui begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// ImGui UI
		ImGui::Begin("Options", 0, ImGuiWindowFlags_NoCollapse);

		ImGui::Text("Debug Menu");
		ImGui::Text("FPS: %f", 1 / deltaTime);

		if (ImGui::Checkbox("Wireframe", &bWireframe))
			bWireframe ? URenderingCommand::WireframeOn() : URenderingCommand::WireframeOff();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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