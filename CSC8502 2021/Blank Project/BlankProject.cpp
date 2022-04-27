#include "../nclgl/window.h"
#include "Renderer.h"

int main() {
	Window w("Island Mapping!", 2560, 1440, true);
	if (!w.HasInitialised()) {
		return -1;
	}

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.UpdateScene(w.GetTimer()->GetTimeDeltaSeconds());
		renderer.RenderScene();
		renderer.SwapBuffers();
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F5)) {
			Shader::ReloadAllShaders();
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_G)) {//press G button enter Multiple viewpoints.
			renderer.changecamera = true;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F)) {//press F button turn back to one viewpoints.
			renderer.changecamera = false;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_H)) {//press H button enter deferred shading.
			renderer.deferred = true;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_J)) {//press J button turn back from deferred shading.
			renderer.deferred= false;
		}

	}
	return 0;
}