// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file standalone/application/ViewPresetListManager.cc
/// @brief This class will pop dialog box when save/delete view presets
/// @author YunchaoLiu (yunchao.liu@vanderbilt.edu)

#include <standalone/application/ViewPresetListManager.hh>

#include <standalone/application/PresetSaveDialog.hh>

#include <interactive/application/shared/ViewOptionsWidget.hh>
#include <interactive/gui/dialogs.hh>
#include <interactive/gui/ModalDialog.hh>
#include <interactive/gui/TopLevel.hh>
#include <interactive/gui/ViewPreset.hh>
#include <interactive/gui/ViewPresetList.hh>
#include <interactive/translate/Translator.hh>
#include <interactive/util/Exception.hh>

#include <basic/Tracer.hh>

static basic::Tracer TR( "standalone.application.ViewPresetListManager" );


namespace standalone {
namespace application {

ViewPresetListManager::ViewPresetListManager(interactive::gui::ViewPresetListOP view_preset_list)
{
	view_preset_list_ = view_preset_list;
}

ViewPresetListManager::~ViewPresetListManager(){

}

ViewPresetListManager::ViewPresetListManager( ViewPresetListManager const & ) {

}



ViewPresetListManagerOP
ViewPresetListManager::clone() const {
	return ViewPresetListManagerOP( new ViewPresetListManager( *this ) );
}


bool
ViewPresetListManager::save_preset_with_dialog(interactive::application::shared::ToolApplication * app, interactive::application::shared::ViewOptionsWidgetAP vw){


	PresetSaveDialogOP preset_save_dialog = new PresetSaveDialog(PresetSaveDialog::SAVE, interactive::gui::TopLevel::instance(), this, app, vw);
	preset_save_dialog->set_visible(true);

}




bool
ViewPresetListManager::edit_preset_with_dialog(interactive::application::shared::ToolApplication * app, interactive::application::shared::ViewOptionsWidgetAP vw){
	if(view_preset_list_->get_current_preset()->get_preset_type()==interactive::gui::ViewPreset::BUILT_IN){
		interactive::gui::message_dialog(vw->get_top_level(), _trx("Cannot edit built-in presets"));
	}
	else{
		PresetSaveDialogOP preset_save_dialog = new PresetSaveDialog(PresetSaveDialog::EDIT, interactive::gui::TopLevel::instance(), this, app, vw);
		preset_save_dialog->set_visible(true);
	}
}

void
ViewPresetListManager::edit_preset(const std::string preset_name){
	view_preset_list_->edit_preset(preset_name);
}


bool
ViewPresetListManager::delete_preset_with_dialog(interactive::application::shared::ToolApplication * app, interactive::application::shared::ViewOptionsWidgetAP vw){

//	core::Size i = interactive::util::dynamic_pointer_cast<interactive::gui::SelectionList>(vw->get_view_preset_widget())->get_selected_widget_index();
//	std::cerr<<"i:"<<i<< " size:" << preset_name_list_.size() << std::endl;
//
//	interactive::gui::ViewPresetOP view_preset= view_preset_list_->get_preset_by_index(i);
	interactive::gui::ViewPresetOP view_preset=view_preset_list_->get_current_preset();
	if(view_preset->get_preset_type() == interactive::gui::ViewPreset::BUILT_IN){
		interactive::gui::message_dialog(vw->get_top_level(), _trx("You cannot delete the default!"));
	}
	else{
		interactive::gui::ModalDialogOP delete_confirm_dialog = interactive::gui::question_dialog(interactive::gui::TopLevel::instance(), false,
				_trx("Are you sure you want to delete this preset?"),
				interactive::gui::ButtonClickCallback(boost::bind(&ViewPresetListManager::delete_preset_and_update_selection_list,this,vw)),//Yes function
				interactive::gui::ButtonClickCallback(),//No function
				true);

		delete_confirm_dialog->set_visible(true);
	}
}


bool
ViewPresetListManager::check_duplicate_view_preset(interactive::gui::ViewPresetOP view_preset){
	//view_preset_list_->is_preset_existed(view_preset);
	view_preset;
}

bool
ViewPresetListManager::check_duplicate_view_preset_name(std::string view_preset_name){
	try{

		TR.Debug<<" check_duplicate_view_preset_name..."<<std::endl;
		return view_preset_list_->is_preset_name_existed(view_preset_name);;
	}
	catch (interactive::util::Exception & e) {
		TR.Debug<<e<<": check_duplicate_view_preset_name correctly"<<std::endl;
		return false;
	}

}


interactive::gui::ViewPresetListOP
ViewPresetListManager::get_view_preset_list(){
	return view_preset_list_;
}





void
ViewPresetListManager::add_preset(interactive::gui::ViewPresetOP view_preset, const bool is_customized, const std::string name){
	view_preset_list_->add_preset(view_preset, is_customized, name);
	std::cerr<<"I'm here3"<<std::endl;
}


bool
ViewPresetListManager::delete_preset_and_update_selection_list(interactive::application::shared::ViewOptionsWidgetAP vw){

	view_preset_list_->delete_preset();

	vw->update_preset_list();
}

} //standalone
} //application






