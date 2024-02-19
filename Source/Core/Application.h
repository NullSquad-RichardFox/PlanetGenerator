#pragma once


class URenderer3D;
class URenderer2D;
class UTime;
class UWindow;

class UApplication
{
public:
	UApplication();
	~UApplication();

	void Initialize();
	void Run();

	// Shuts down the application after a window has been closed
	void WindowClosed();

	inline static UApplication* GetApplication() { return sInstance; }
	inline const std::shared_ptr<UWindow>& GetWindow() const { return GameWindow; }

private:
	static UApplication* sInstance;

	std::shared_ptr<URenderer2D> Renderer2D;
	std::shared_ptr<URenderer3D> Renderer3D;
	std::shared_ptr<UTime> TimeHandle;
	std::shared_ptr<UWindow> GameWindow;

	bool bRunning;
};

// Global application getter function
static UApplication* GetApp() { return UApplication::GetApplication(); }