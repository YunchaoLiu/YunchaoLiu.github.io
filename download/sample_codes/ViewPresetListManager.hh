// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file standalone/application/ViewPresetListManager.hh
/// @brief This class will pop dialog box when save/delete view presets
/// @author YunchaoLiu (yunchao.liu@vanderbilt.edu)


#ifndef INCLUDED_STANDALONE_APPLICATION_VIEWPRESETLISTMANAGER_HH
#define INCLUDED_STANDALONE_APPLICATION_VIEWPRESETLISTMANAGER_HH

#include <standalone/application/ViewPresetListManager.fwd.hh>

#include <interactive/application/shared/ToolApplication.hh>
#include <interactive/application/shared/ViewOptionsWidget.fwd.hh>
#include <interactive/gui/ViewPreset.fwd.hh>
#include <interactive/gui/ViewPresetList.fwd.hh>

// Utility headers
#include <interactive/util/refcount/ReferenceCount.hh>

namespace standalone {
namespace application {

///@brief This class will pop dialog box when save/delete view presets
class ViewPresetListManager : public interactive::util::ReferenceCount{

public:

	ViewPresetListManager(interactive::gui::ViewPresetListOP view_preset_list);
	ViewPresetListManager(ViewPresetListManager const & src);

	virtual ~ViewPresetListManager();

	ViewPresetListManagerOP
	clone() const;

	bool
	save_preset_with_dialog(interactive::application::shared::ToolApplication * app, interactive::application::shared::ViewOptionsWidgetAP vw);

	void
	add_preset(interactive::gui::ViewPresetOP view_preset, const bool is_customized,const std::string name);

	bool
	edit_preset_with_dialog(interactive::application::shared::ToolApplication * app, interactive::application::shared::ViewOptionsWidgetAP vw);

	void
	edit_preset(const std::string preset_name);

	bool
	delete_preset_with_dialog(interactive::application::shared::ToolApplication * app, interactive::application::shared::ViewOptionsWidgetAP vw);

	bool
	check_duplicate_view_preset(interactive::gui::ViewPresetOP view_preset);

	bool
	check_duplicate_view_preset_name(std::string view_preset_name);

	interactive::gui::ViewPresetListOP
	get_view_preset_list();





private:
	interactive::gui::ViewPresetListOP view_preset_list_;

	bool
	delete_preset_and_update_selection_list(interactive::application::shared::ViewOptionsWidgetAP vw);

};


} //standalone
} //application



#endif //INCLUDED_STANDALONE_APPLICATION_VIEWPRESETLISTMANAGER_HH





