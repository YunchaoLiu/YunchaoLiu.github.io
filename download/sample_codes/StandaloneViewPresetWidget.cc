// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#include <standalone/application/StandaloneViewPresetWidget.hh>

#include <standalone/application/StandalonePreset.hh>
#include <standalone/application/StandaloneViewOptionsWidget.hh>
#include <interactive/gui/Container.hh>
#include <interactive/gui/HidePanel.hh>
#include <interactive/gui/SelectionList.hh>
#include <interactive/gui/StaticUniText.hh>
#include <interactive/gui/TextButton.hh>
#include <interactive/translate/Translator.hh>

namespace standalone {
namespace application {

static const int PANEL_WIDTH = 270;
static const int BUTTON_WIDTH = 160;

StandaloneViewPresetWidget::StandaloneViewPresetWidget(StandaloneApplication * game) :
		StandaloneViewOptionsWidget(game),
		novice_game_(game)
{



	more_view_options_btn_ = new interactive::gui::TextButton();
	more_view_options_btn_->set_horizontal_alignment(
			interactive::gui::StaticUniText::HA_CENTER);
	more_view_options_btn_->set_vertical_alignment(
			interactive::gui::StaticUniText::VA_MIDDLE);
	more_view_options_btn_->set_font_size(interactive::gui::SMALL_FONT);
	more_view_options_btn_->set_text(_trx("More View Options"));
	more_view_options_btn_->set_size(BUTTON_WIDTH, 20);
	more_view_options_btn_->set_pos(40, 0);
	more_view_options_btn_->set_click_callback(
			boost::bind(&StandaloneViewPresetWidget::open_view_option_widget, this));
	more_view_options_btn_->set_disabled(false);
	std::cerr << "initialized StandaloneViewPresetWidget" << std::endl;

}

StandaloneViewPresetWidget::~StandaloneViewPresetWidget() {

}

void StandaloneViewPresetWidget::do_layout_widgets(
		interactive::gui::ContainerLayout & left_side_layout,
		interactive::gui::ContainerLayout & right_side_layout) {

	interactive::gui::ContainerLayout * side_layout = NULL;

	side_layout = &left_side_layout;
	side_layout->add_widget(get_view_preset_title_widget());
	side_layout->add_widget(get_view_preset_widget());
	side_layout->add_widget(more_view_options_btn_);

}

void StandaloneViewPresetWidget::open_view_option_widget() {
	std::cerr << "open_view_option_widget" << std::endl;
	novice_game_->toggle_view_options_widget();

}

void StandaloneViewPresetWidget::on_refresh() {



	// this will deparent widgets so we can later tell which they were added
	clear_widgets();



	//codes for single column layout start here
	left_side_->clear_widgets();
	right_side_->clear_widgets();

	interactive::gui::ContainerLayout left_side_layout(left_side_.get(),
			interactive::gui::ContainerLayout::VERTICAL_TOP_TO_BOTTOM, PANEL_WIDTH);
	interactive::gui::ContainerLayout right_side_layout(right_side_.get(),
			interactive::gui::ContainerLayout::VERTICAL_TOP_TO_BOTTOM, 1);

	do_layout_widgets(left_side_layout, right_side_layout);

	left_side_layout.do_layout();
	right_side_layout.do_layout();

	core::Real height = std::max(left_side_->size().h().abs(),
			right_side_->size().h().abs());
	interactive::gui::ContainerLayout main_layout(this, interactive::gui::ContainerLayout::HORIZONTAL_LEFT_TO_RIGHT,
			height);
	main_layout.set_default_non_direction_pos(interactive::gui::UDim::TOP);

	main_layout.add_widget(left_side_);
	main_layout.add_widget(right_side_);

	//codes for single column layout end here

	main_layout.do_layout();
}

} //application
} //standalone
