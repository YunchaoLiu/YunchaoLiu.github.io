// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file interactive/gui/ViewPresetList.fwd.hh
/// @brief A class that manages ViewPreset
/// @author YunchaoLiu (yunchao.liu@vanderbilt.edu)

#ifndef INCLUDED_INTERACTIVE_GUI_VIEWPRESETLIST_FWD_HH
#define INCLUDED_INTERACTIVE_GUI_VIEWPRESETLIST_FWD_HH

// Utility headers
#include <utility/vector1.hh>
#include <interactive/util/refcount/access_ptr.hh>
#include <interactive/util/refcount/owning_ptr.hh>


// Forward
namespace interactive {
namespace gui {

class ViewPresetList;

typedef interactive::util::access_ptr< ViewPresetList > ViewPresetListAP;
typedef interactive::util::access_ptr< ViewPresetList const > ViewPresetListCAP;
typedef interactive::util::owning_ptr< ViewPresetList > ViewPresetListOP;
typedef interactive::util::owning_ptr< ViewPresetList const > ViewPresetListCOP;
typedef utility::vector1< ViewPresetListOP > ViewPresetListOPs;
typedef utility::vector1< ViewPresetListCAP >  ViewPresetListCAPs;

} //interactive
} //gui

#endif //INCLUDED_INTERACTIVE_GUI_VIEWPRESETLIST_FWD_HH
