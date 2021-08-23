// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#ifndef INCLUDED__STANDALONE_APPLICATION_STANDALONEVIEWPRESETWIDGET_HH
#define INCLUDED__STANDALONE_APPLICATION_STANDALONEVIEWPRESETWIDGET_HH

#include <standalone/application/StandaloneViewPresetWidget.fwd.hh>

#include <standalone/application/StandaloneApplication.hh>
#include <standalone/application/StandaloneViewOptionsWidget.hh>

#include <interactive/application/shared/ViewOptionsWidget.hh>
#include <interactive/gui/ContainerLayout.hh>
#include <interactive/gui/TextButton.fwd.hh>


namespace standalone {
namespace application {

class StandaloneViewPresetWidget: public StandaloneViewOptionsWidget, public shared::StandaloneApplicationObserver
{
public:
	//Constructor
	StandaloneViewPresetWidget(StandaloneApplication * game);

	/// Destructor
	virtual
	~StandaloneViewPresetWidget();

	virtual
	void
	do_layout_widgets(interactive::gui::ContainerLayout & left_side_layout,
			interactive::gui::ContainerLayout & right_side_layout);

private:


	void
	open_view_option_widget();

	void
	on_refresh();



	StandaloneApplication * novice_game_;
	interactive::gui::TextButtonOP more_view_options_btn_;
	StandaloneViewOptionsWidgetOP view_options_widget_;
};

} //application
} //standalone

#endif //INCLUDED__STANDALONE_APPLICATION_STANDALONEVIEWPRESETWIDGET_HH
