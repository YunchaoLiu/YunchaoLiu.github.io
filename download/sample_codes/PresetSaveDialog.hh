// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#ifndef INCLUDED__STANDALONE_APPLICATION_PRESET_SAVE_DIALOG_HH
#define INCLUDED__STANDALONE_APPLICATION_PRESET_SAVE_DIALOG_HH

#include <standalone/application/PresetSaveDialog.fwd.hh>

#include <standalone/application/SolutionMetadata.fwd.hh>
#include <standalone/application/StandalonePreset.fwd.hh>
#include <standalone/application/ViewPresetListManager.fwd.hh>
#include <standalone/application/boinc/BoincKey.hh>

#include <interactive/application/shared/ToolApplication.fwd.hh>
#include <interactive/application/shared/ViewOptionsWidget.fwd.hh>
#include <interactive/gui/Container.fwd.hh>
#include <interactive/gui/ModalDialog.hh>
#include <interactive/gui/ViewPreset.fwd.hh>
#include <interactive/gui/ViewPresetList.fwd.hh>
#include <interactive/gui/StaticUniText.fwd.hh>
#include <interactive/gui/TextBox.fwd.hh>

namespace standalone {
namespace application {

class PresetSaveDialog : public interactive::gui::ModalDialog
{

public:

	/// Is this dialog for saving solutions or editting solution descriptions.
	typedef enum {
		EDIT = 0,     ///< The user is editting an existing solution
		SAVE,         ///< The user is saving a new solution
	} DialogType;

	/// Called right after this dialog is closed.
	typedef boost::function< void (SolutionMetadataOP) > SolutionCallback;

	/// Called to see the load/save dialog
	typedef boost::function< void () > ClickCallback;

	/// Creates a solution dialog
	/// \param parent The parent container of this dialog
	/// \param show_solutions_button Whether to show the "See Solutions" button
	PresetSaveDialog(DialogType type,
					 interactive::gui::ContainerAP parent,
					 ViewPresetListManagerOP preset_table_manager,
					 interactive::application::shared::ToolApplicationAP app,
					 interactive::application::shared::ViewOptionsWidgetAP vw
					 );

	virtual
	~PresetSaveDialog();


	/// Called after the user hits "save" in save mode (or "close" in
	/// edit mode) after the dialog is made invisible. The value passed
	/// into the solution callback is the editted solution.
	void
	set_on_save_callback(SolutionCallback save_callback);


	/// Provides special functionality when the user make this dialog visible
	virtual
	void
	set_visible(bool visible);



private:

	/// Creates the GUI for this dialog.



	void
	create_gui(DialogType type,
			   interactive::application::shared::ToolApplicationAP app,
			   interactive::application::shared::ViewOptionsWidgetAP vw,
			   interactive::gui::ViewPresetListAP view_preset_table
			   );

	/// Makes this dialog invisible, calling the callback if necessary
	void
	close(bool cancel,
		  DialogType type,
		  interactive::application::shared::ToolApplicationAP app,
		  interactive::application::shared::ViewOptionsWidgetAP vw,
		  interactive::gui::ViewPresetListAP view_preset_table
		  );

	//check if the string is alphanumric, has dash/underscore or not
	bool
	is_string_valid(std::string input_string);

	static
	bool
	char_not_valid(char c);



	/// Stores the name.
	interactive::gui::TextBoxOP name_input_;



	/// Called when the user hits save.
	SolutionCallback save_callback_;

	/// Called when the user hits close.
	SolutionCallback close_callback_;

	interactive::gui::ViewPresetAP current_preset_;
	ViewPresetListManagerOP preset_table_manager_;
};


} // namespace application
} // namespace standalone


#endif // INCLUDED__STANDALONE_APPLICATION_PRESET_SAVE_DIALOG_HH


