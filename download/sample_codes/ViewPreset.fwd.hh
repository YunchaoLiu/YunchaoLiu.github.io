// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#ifndef INCLUDED__INTERACTIVE_GUI_VIEW_PRESET_FWD_HH
#define INCLUDED__INTERACTIVE_GUI_VIEW_PRESET_FWD_HH

#include <utility/vector1.hh>
#include <interactive/util/refcount/access_ptr.hh>
#include <interactive/util/refcount/owning_ptr.hh>

namespace interactive {
namespace gui {

class ViewPreset;
typedef interactive::util::access_ptr< ViewPreset > ViewPresetAP;
typedef interactive::util::access_ptr< ViewPreset const > ViewPresetCAP;
typedef interactive::util::owning_ptr< ViewPreset > ViewPresetOP;
typedef interactive::util::owning_ptr< ViewPreset const > ViewPresetCOP;

} // namespace gui
} // namespace interactive

#endif // INCLUDED__INTERACTIVE_GUI_VIEW_PRESET_FWD_HH
