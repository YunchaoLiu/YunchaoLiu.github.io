// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file interactive/gui/ViewPresetList.hh
/// @brief A class that manages a list of ViewPreset
/// @author YunchaoLiu (yunchao.liu@vanderbilt.edu)


#ifndef INCLUDED_INTERACTIVE_GUI_VIEWPRESETMANAGER_HH
#define INCLUDED_INTERACTIVE_GUI_VIEWPRESETMANAGER_HH

#include <interactive/gui/ViewPresetList.fwd.hh>



#include <interactive/application/shared/ViewOptionsWidget.fwd.hh>
#include <interactive/gui/ViewPreset.hh>
#include <core/types.hh>

// Utility headers
#include <interactive/util/refcount/ReferenceCount.hh>


//forward declaration for friend class
namespace standalone{namespace application{ class ViewPresetListManager;}}

namespace interactive {
namespace gui {

///@brief A class that manage a list of ViewPreset
class ViewPresetList : public interactive::util::ReferenceCount {



public:

	ViewPresetList();
	ViewPresetList(ViewPresetList const & src);

	virtual ~ViewPresetList();


	bool
	load_presets();

	bool
	save_presets_to_file()const;

	ViewPresetAP
	get_preset_by_name(const std::string preset_name)const;

	int
	get_index_by_name(const std::string preset_name)const;

	ViewPresetAP
	get_preset_by_index(const core::Size index) const;

	std::string
	get_preset_name_by_index(const core::Size index) const;


	ViewPresetAP
	get_current_preset() const;

	int
	get_current_preset_index() const;


	void
	set_index_x_as_current_preset(const core::Size index);

	int
	get_list_size() const;


	bool
	is_preset_name_existed(const std::string view_preset_name) const;



protected:


private:

	std::vector<ViewPresetOP> preset_table_;
	int current_preset_index_;

	void
	add_preset(ViewPresetOP preset, const bool is_customized, const std::string name);

	void
	edit_preset(const std::string & preset_name);

	bool
	delete_preset();


	bool
	load_built_in_presets(const std::string & path);

	bool
	load_customized_presets();

	void
	save_customized_preset_names_to_file() const;

	bool
	save_customized_presets_to_file() const;

	friend class standalone::application::ViewPresetListManager;

};


} //interactive
} //gui



#endif //INCLUDED_INTERACTIVE_GUI_VIEWPRESETMANAGER_HH





