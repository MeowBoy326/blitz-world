#include "imguiex.h"

using namespace wb;

namespace ImGuiEx {

bool Checkbox(const char* label, BoolProperty& v) {
	auto value = v.value();
	if (!ImGui::Checkbox(label, &value)) return false;
	v = value;
	return true;
}

bool InputInt(const char* label, IntProperty& v, int step, int step_fast, ImGuiInputTextFlags flags) {
	auto value = v.value();
	if (!ImGui::InputInt(label, &value, step, step_fast, flags)) return false;
	v = value;
	return true;
}

bool DragFloat(const char* label, wb::FloatProperty& v, float v_speed, float v_min, float v_max, const char* format,
			   ImGuiSliderFlags flags) {
	auto value = v.value();
	if (!ImGui::DragFloat(label, &value, v_speed, v_min, v_max, format, flags)) return false;
	v = value;
	return true;
}

bool FilePath(const char* label, wb::StringProperty& v, const char* dialogTitle, const char* vFilters) {

	String dialogKey = "[" + String(label) + "]";

	if (ImGui::Button(label)) { ImGuiFileDialog::Instance()->OpenDialog(dialogKey, dialogTitle, vFilters, "."); }

	if (!ImGuiFileDialog::Instance()->Display(dialogKey)) return false;

	bool ok = false;
	// action if OK
	if (ImGuiFileDialog::Instance()->IsOk()) {
		v = ImGuiFileDialog::Instance()->GetFilePathName();
		ok = true;
	}

	// close
	ImGuiFileDialog::Instance()->Close();
	return ok;
}

bool ColorEdit4(const char* label, wb::Property<wb::Vec4f>& v, ImGuiColorEditFlags flags) {
	auto value = v.value();
	if (!ImGui::ColorEdit4(label, &value.x, flags)) return false;
	v = value;
	return true;
}

bool ColorPicker4(const char* label, wb::Property<wb::Vec4f>& v, ImGuiColorEditFlags flags, const float* ref_col) {
	auto value = v.value();
	if (!ImGui::ColorPicker4(label, &value.x, flags)) return false;
	v = value;
	return true;
}

} // namespace ImGuiEx
