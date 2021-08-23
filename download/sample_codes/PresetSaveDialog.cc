// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#include <standalone/application/PresetSaveDialog.hh>

#include <standalone/application/boinc/Puzzle.hh>
#include <standalone/application/SolutionMetadata.hh>
#include <standalone/application/StandalonePreset.hh>
#include <standalone/application/ViewPresetListManager.hh>

#include <interactive/application/shared/ToolApplication.hh>
#include <interactive/application/shared/ViewOptionsWidget.hh>
#include <interactive/gui/GUIMutex.hh>
#include <interactive/util/resources.hh>
#include <interactive/gui/Button.hh>
#include <interactive/gui/Container.hh>
#include <interactive/gui/ContainerLayout.hh>
#include <interactive/gui/dialogs.hh>
#include <interactive/gui/Point2D.hh>
#include <interactive/gui/StaticUniText.hh>
#include <interactive/gui/TextBox.hh>
#include <interactive/gui/TopLevel.hh>
#include <interactive/gui/ViewPreset.hh>
#include <interactive/gui/ViewPresetList.hh>
#include <interactive/gui/Widget.hh>
#include <interactive/translate/Translator.hh>
#include <interactive/util/rosetta_util.hh>
//#include <interactive/util/options_dict.hh>


#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

using namespace interactive::gui;

namespace standalone {
namespace application {

PresetSaveDialog::PresetSaveDialog(DialogType type,
								   interactive::gui::ContainerAP parent,
								   ViewPresetListManagerOP preset_table_manager,
								   interactive::application::shared::ToolApplicationAP app,
								   interactive::application::shared::ViewOptionsWidgetAP vw)
{	parent->add_widget(this);
	preset_table_manager_ = preset_table_manager;
	current_preset_ = preset_table_manager_->get_view_preset_list()->get_current_preset();
	create_gui(type, app, vw, preset_table_manager->get_view_preset_list());
}


PresetSaveDialog::~PresetSaveDialog()
{
	// destructor - do nothing
}



void
PresetSaveDialog::set_on_save_callback(SolutionCallback save_callback)
{
	save_callback_ = save_callback;
}



void
PresetSaveDialog::set_visible(bool visible)
{
	ModalDialog::set_visible(visible);
	if (visible) {
		get_top_level()->take_keyboard_focus(name_input_);
	}
}



static
WidgetOP
spacer_(core::Size pixels)
{
	WidgetOP spacer = new Widget();
	spacer->set_size(pixels, pixels);
	return spacer;
}


void
PresetSaveDialog::create_gui(DialogType type,
							interactive::application::shared::ToolApplicationAP app,
							interactive::application::shared::ViewOptionsWidgetAP vw,
							interactive::gui::ViewPresetListAP view_preset_table)
{
	const Size DIALOG_WIDTH = 350;
	const Size BUTTON_WIDTH = 80;
	const Size DIALOG_BORDER = 10;
	const Size TITLE_HEIGHT = 25;
	
	PanelAP panel = get_panel();
	
	// basic dialos positioning
	panel->set_rounded_corners(true);
	panel->set_pos(UDim::CENTER, UDim::CENTER);

	PanelOP title_panel = new Panel();
	title_panel->set_size(UDim::rel(1.0) - 2 * DIALOG_BORDER, TITLE_HEIGHT);
	title_panel->set_color(core::Vector(1.0, 1.0, 1.0), 0.2);
	title_panel->set_rounded_corners(true);
	
	StaticUniTextOP title_text = new StaticUniText();
	title_text->set_size(UDim::rel(1.0) - 2 * DIALOG_BORDER, UDim::rel(1.0));
	title_text->set_pos(UDim::CENTER, UDim::CENTER);
	title_text->set_horizontal_alignment(StaticUniText::HA_CENTER);
	title_text->set_vertical_alignment(StaticUniText::VA_MIDDLE);
	switch (type) {
	case EDIT:
		title_text->set_text(_trx("Edit Preset"));

		break;
	case SAVE:
		title_text->set_text(_trx("Save Preset"));
		break;
	default:
		THROW_EXCEPTION(boost::str(boost::format(_trx("PresetSaveDialog type %i unknown.")) % type));
		break;
	}
	title_panel->add_widget(title_text);

	StaticUniTextOP name_title = new StaticUniText();
	name_title->set_size(UDim::rel(1.0) - 2 * DIALOG_BORDER, 20);
	name_title->set_text(_trx("Preset Name:"));
	name_title->set_font_size(MEDIUM_FONT);
	name_title->set_horizontal_alignment(StaticUniText::HA_LEFT);
	name_title->set_vertical_alignment(StaticUniText::VA_MIDDLE);

	name_input_ = new TextBox(true);
	name_input_->set_size(UDim::rel(1.0) - 2 * DIALOG_BORDER, 24);
	name_input_->set_font_size(SMALL_FONT);
	name_input_->set_tooltip_text(_trx("A name for this preset."));
	if(type == EDIT ){
		name_input_->set_text_without_callback(current_preset_->get_preset_name());
	}
	name_input_->set_enter_callback(boost::bind(&PresetSaveDialog::set_visible, this, false));



	// Button that saves this dialog.
	ButtonOP save_button = new Button();
	save_button->set_size(BUTTON_WIDTH, UDim::rel(1.0));
	save_button->set_icon_image(interactive::util::resource_full_name("images/32x32/document-save-as.png"));
	save_button->set_text("Save");
	save_button->set_click_callback(boost::bind(&PresetSaveDialog::close, this, false, type, app, vw, view_preset_table));
	
	// Button that closes this dialog.
	ButtonOP cancel_button = new Button();
	cancel_button->set_size(BUTTON_WIDTH, UDim::rel(1.0));
	cancel_button->set_icon_image(interactive::util::resource_full_name("images/32x32/emblem-unreadable.png"));
	cancel_button->set_text(_trx("Cancel"));
	cancel_button->set_click_callback(boost::bind(&PresetSaveDialog::close, this, true, type, app, vw, view_preset_table));

	
	// Layout the buttons
	ContainerOP buttons = new Container();
	ContainerLayout button_layout(buttons.get(), ContainerLayout::HORIZONTAL_LEFT_TO_RIGHT, 60);
	switch (type) {
	case EDIT:

		button_layout.add_widget(cancel_button);
		button_layout.add_widget(save_button);

		break;
	case SAVE:
		button_layout.add_widget(cancel_button);
		button_layout.add_widget(save_button);
		break;

	default:
		THROW_EXCEPTION(boost::str(boost::format("PresetSaveDialog type %i unknown.") % type));
		break;
	}
	button_layout.do_layout();
	
	// Layout the whole container.
	ContainerLayout main_layout(panel, ContainerLayout::VERTICAL_TOP_TO_BOTTOM, DIALOG_WIDTH - 20);
	main_layout.add_widget(spacer_(5));
	main_layout.add_widget(title_panel);
	main_layout.add_widget(spacer_(3));
	main_layout.add_widget(name_title);
	main_layout.add_widget(name_input_);
	main_layout.add_widget(spacer_(5));
	main_layout.add_widget(buttons);
	main_layout.do_layout();

	// keyboard behavior
	name_input_->set_enter_callback(boost::bind(&PresetSaveDialog::close, this, false, type, app,vw, view_preset_table));

}

void
PresetSaveDialog::close(bool cancel,
						DialogType type,
						interactive::application::shared::ToolApplicationAP app,
						interactive::application::shared::ViewOptionsWidgetAP vw,
						interactive::gui::ViewPresetListAP view_preset_table
						)
{
	if (cancel) {
		set_visible(false);
		return;
	}
	std::string name=name_input_->get_text();
		
	// make sure that the input is correct
	const Size name_length = name.length();
	if (name_length < 1 || name_length > 27) {
		message_dialog(get_top_level(), _trx("Name must be between 1 and 26 characters."));
		return;
	}

	if(!is_string_valid(name)){
		message_dialog(get_top_level(), _trx("Name can only contain alphanumeric, dash, or underscore" ));
		return;
	}

	if(preset_table_manager_->check_duplicate_view_preset_name(name)){
		message_dialog(get_top_level(), _trx("Preset name exist!"));
		return;
	}
	else
	{
		if(type == SAVE){
			ViewPresetOP new_preset = new ViewPreset(name);

			new_preset->get_settings_from_app(app);

		    preset_table_manager_->add_preset(new_preset, true, name);
			vw->update_preset_list();


		}
		else{
			preset_table_manager_->edit_preset(name_input_->get_text());
			//preset_table_manager_->get_view_preset_list()->get_current_preset()->set_preset_name(name_input_->get_text());
			//preset_table_manager_->get_view_preset_list()->save_presets_to_file();
			vw->update_preset_list();

		}
		message_dialog(get_top_level(), _trx("Preset saved"));




		// everything was fine... save the solution
		set_visible(false);
//		if (!cancel && bool(save_callback_)) {
//
//			//save_callback_(metadata_);
//		}

		return;
	}
}

bool
PresetSaveDialog::is_string_valid(std::string input_string){
	bool result = find_if(input_string.begin(), input_string.end(), PresetSaveDialog::char_not_valid) == input_string.end();
	//std::cerr<<"PresetSaveDialog.cc:result:"<<result<<std::endl;
	return result;
}

bool
PresetSaveDialog::char_not_valid(char c){
	//std::cerr<<"char c:"<<c<<" !isalum:"<<!std::isalnum(c)<<std::endl;
	return !std::isalnum(c) && (c!='_') && (c!='-');
};




} // namespace application
} // namespace standalone
