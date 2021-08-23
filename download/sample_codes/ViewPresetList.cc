// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file interactive/gui/ViewPresetList.cc
/// @brief A class that manages a list of ViewPreset
/// @author YunchaoLiu (yunchao.liu@vanderbilt.edu)

#include <interactive/gui/ViewPresetList.hh>

#include <interactive/application/shared/ViewOptionsWidget.hh>
#include <interactive/gui/ViewPreset.hh>
#include <interactive/util/Dictionary.hh>
#include <interactive/util/Exception.hh>
#include <interactive/util/general_util.hh>
#include <interactive/util/path.hh>
#include <interactive/util/options_dict.hh>
#include <interactive/util/resources.hh>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <utility/file/FileName.hh>

#include <fstream>

#include <basic/Tracer.hh>

static basic::Tracer TR("interactive.gui.ViewPresetList");

namespace interactive {
namespace gui {

static const std::string BUILT_IN_PRESET_FOLDER_NAME_ = "view-presets";
static const std::string CUSTOMIZED_PRESET_FOLDER_NAME_ = "view-presets";
static const std::string BUILT_IN_PRESET_NAME_SUFFIX = " [built-in]";
static const std::string CUSTOMIZED_VIEW_PRESET_NAMES_TAG = "preset_names";
static interactive::util::DictionaryOP built_in_presets_dict_;
static interactive::util::DictionaryOP customized_presets_dict_;




ViewPresetList::ViewPresetList() {
	TR.Debug << "ViewPresetList is initialing" << std::endl;
	load_presets();

}

ViewPresetList::~ViewPresetList() {

}

ViewPresetList::ViewPresetList(ViewPresetList const &) {

}

bool ViewPresetList::load_presets() {
	//default "New" preset
	ViewPresetOP view_preset = new ViewPreset("New");
	view_preset->set_preset_type(ViewPreset::BUILT_IN);
	preset_table_.push_back(view_preset);


	if (load_built_in_presets(BUILT_IN_PRESET_FOLDER_NAME_) && load_customized_presets()) {
//		TR.Debug<<"preset list after loading"<<std::endl;
//		for(std::vector<ViewPresetOP>::iterator it = preset_table_.begin(); it != preset_table_.end();it++){
//			TR.Debug<<"i:"<<it-preset_table_.begin()<<(*it)->get_preset_name()<<std::endl;
//		}

		TR.Info << "successfully load both built-in and customized presets into list" << std::endl;
		return true;
	} else {
		TR.Error << "error in loading presets into list" << std::endl;
		return false;
	}
}


bool
ViewPresetList::save_presets_to_file()const{
	save_customized_preset_names_to_file();
	save_customized_presets_to_file();
};

void ViewPresetList::add_preset(ViewPresetOP preset, const bool is_customized, const std::string name) {

	if(is_customized){
		preset->set_preset_type(ViewPreset::CUSTOMIZED);
	}
	else{
		preset->set_preset_type(ViewPreset::BUILT_IN);
	}
	preset->set_preset_name(name);

	preset_table_.push_back(preset);
	int index = preset_table_.size()-1;
	set_index_x_as_current_preset(index);

	save_presets_to_file();
}

void
ViewPresetList::edit_preset(const std::string & preset_name){
	std::string old_name = preset_table_[current_preset_index_] ->get_preset_name();
	interactive::util::Dictionary * pre_dict = &interactive::util::presets_dict();
	preset_table_[current_preset_index_]->delete_settings_from_dict(pre_dict, old_name+"/");
	preset_table_[current_preset_index_]->set_preset_name(preset_name);

	save_presets_to_file();

}


bool
ViewPresetList::delete_preset() {

	std::string preset_name= preset_table_[current_preset_index_]->get_preset_name();

	interactive::util::Dictionary * pre_dict = &interactive::util::presets_dict();
	preset_table_[current_preset_index_]->delete_settings_from_dict(pre_dict, preset_name+"/");


	preset_table_.erase(preset_table_.begin()+current_preset_index_);
	set_index_x_as_current_preset(0);

	save_customized_preset_names_to_file();
	return true;

}



ViewPresetAP
ViewPresetList::get_preset_by_name(std::string preset_name) const {
	for (std::vector<ViewPresetOP>::const_iterator it = preset_table_.begin(); it != preset_table_.end(); ++it) {
		if (!preset_name.compare((*it)->get_preset_name())) {
			return *it;
		}
	}
	return ViewPresetAP();
}

int
ViewPresetList::get_index_by_name(const std::string preset_name)const{
	for (std::vector<ViewPresetOP>::const_iterator it = preset_table_.begin(); it != preset_table_.end(); ++it) {
		if (!preset_name.compare((*it)->get_preset_name())) {
			return it-preset_table_.begin();
		}
	}
	return 0;
}

ViewPresetAP
ViewPresetList::get_preset_by_index(core::Size index) const {

	return preset_table_[index];
}

std::string ViewPresetList::get_preset_name_by_index(core::Size index) const {
	std::string name = preset_table_[index]->get_preset_name();
	return name;

}

ViewPresetAP
ViewPresetList::get_current_preset() const {
	return preset_table_[current_preset_index_];
}

int ViewPresetList::get_current_preset_index() const {

	return current_preset_index_;
};


void
ViewPresetList::set_index_x_as_current_preset(const core::Size index){
	TR.Debug<<"set current preset to"<<index<<std::endl;//", name:"<<current_preset_->get_preset_name()<<std::endl;
	current_preset_index_ = index;
}



int ViewPresetList::get_list_size() const {
	return preset_table_.size();
}



bool ViewPresetList::is_preset_name_existed(std::string view_preset_name) const {
	for(std::vector<ViewPresetOP>::const_iterator it = preset_table_.begin();it!=preset_table_.end();it++){
		if(!view_preset_name.compare((*it)->get_preset_name())){
			//TR.Debug<<"preset_name existed"<<std::endl;
			return true;
		}

	}
	//TR.Debug<<"preset_name not existed"<<std::endl;
	return false;

}

bool
ViewPresetList::load_built_in_presets(const std::string & path) {
	std::vector<std::string> file_names;
	std::vector<std::string> preset_names;
	std::string full_built_in_preset_folder_name_ = interactive::util::resource_full_name(path);
	try {
		interactive::util::list_files(file_names, full_built_in_preset_folder_name_, interactive::util::LIST_FILES, ".preset");
	} catch (util::Exception & e) {
		TR.Error << e << std::endl;
		return false;
	}
	for (size_t ii = 0; ii < file_names.size(); ++ii) {
		utility::file::FileName ff = file_names.at(ii);
		std::string preset_name = ff.base() + BUILT_IN_PRESET_NAME_SUFFIX;

		preset_names.push_back(preset_name);

		std::string full_name = full_built_in_preset_folder_name_ + "/";
		full_name += ff().c_str();


		built_in_presets_dict_ = new interactive::util::Dictionary();

		// open application presets file
		try {

			std::ifstream presets_file(full_name);
			if (presets_file) {
				interactive::util::read_dictionary_version_1(presets_file, *built_in_presets_dict_);

				ViewPresetOP view_preset = new ViewPreset(preset_name);
				view_preset->set_preset_type(ViewPreset::BUILT_IN);

				view_preset->get_settings_from_dict(built_in_presets_dict_, "");

				preset_table_.push_back(view_preset);

			} else {
				std::cout << "Note (not an error): can't open presets file " << full_name << "; using defaults." << std::endl;
			}

		} catch (util::Exception & e) {
			TR.Info << "Error:" << e << std::endl;
		}
	}

	TR.Info << "successfully loaded built-in preset " << std::endl;
	return true;
};



bool
ViewPresetList::load_customized_presets() {


	try {
		std::vector<std::string> customized_preset_names;
		interactive::util::Dictionary * customized_pre_dict = &interactive::util::presets_dict();
		std::string value;
		customized_pre_dict->get(CUSTOMIZED_VIEW_PRESET_NAMES_TAG, value);


		boost::algorithm::split(customized_preset_names, value, boost::algorithm::is_any_of(";"));
		TR.Debug << "customized preset name:" << value << "end"<< std::endl;
		if(strcmp(value.c_str(),"")){
			for (std::vector<std::string>::iterator it = customized_preset_names.begin(); it != customized_preset_names.end(); ++it) {
				ViewPresetOP view_preset = new ViewPreset(*it);
				view_preset->set_preset_type(ViewPreset::CUSTOMIZED);

				view_preset->get_settings_from_dict(customized_pre_dict, (*it)+"/");

				preset_table_.push_back(view_preset);

			}
		}

	} catch (util::Exception & e) {
		TR.Error << "Error:" << e << std::endl;
		return false;
	}
	return true;
};



void
ViewPresetList::save_customized_preset_names_to_file() const{

	interactive::util::Dictionary & pre_dict = interactive::util::presets_dict();
	std::string value ="";


	for(std::vector<ViewPresetOP>::const_iterator it = preset_table_.begin();it!=preset_table_.end();it++){
		if((*it)->get_preset_type()==ViewPreset::CUSTOMIZED){
			value += ((*it)->get_preset_name() + ";");
		}
	}


	if(std::strcmp(value.c_str(), "")){
		value.erase( value.begin() + value.size() - 1);
	}

	pre_dict.set(CUSTOMIZED_VIEW_PRESET_NAMES_TAG, value);

	util::save_presets_file();
};



bool
ViewPresetList::save_customized_presets_to_file() const {
	std::string preset_name= preset_table_[current_preset_index_]->get_preset_name();


	interactive::util::Dictionary * customized_pre_dict = &interactive::util::presets_dict();

	preset_table_[current_preset_index_]->save_settings_to_dict(customized_pre_dict, preset_name+"/");

};



} //interactive
} //gui

