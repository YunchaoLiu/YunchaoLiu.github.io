// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file standalone/application/ViewPresetListManager.fwd.hh
/// @brief This class will pop dialog box when save/delete view presets
/// @author YunchaoLiu (yunchao.liu@vanderbilt.edu)

#ifndef INCLUDED_STANDALONE_APPLICATION_VIEWPRESETLISTMANAGER_FWD_HH
#define INCLUDED_STANDALONE_APPLICATION_VIEWPRESETLISTMANAGER_FWD_HH

// Utility headers
#include <utility/vector1.hh>
#include <interactive/util/refcount/access_ptr.hh>
#include <interactive/util/refcount/owning_ptr.hh>


// Forward
namespace standalone {
namespace application {

class ViewPresetListManager;

typedef interactive::util::access_ptr< ViewPresetListManager > ViewPresetListManagerAP;
typedef interactive::util::access_ptr< ViewPresetListManager const > ViewPresetListManagerCAP;
typedef interactive::util::owning_ptr< ViewPresetListManager > ViewPresetListManagerOP;
typedef interactive::util::owning_ptr< ViewPresetListManager const > ViewPresetListManagerCOP;
typedef utility::vector1< ViewPresetListManagerOP > ViewPresetListManagerOPs;
typedef utility::vector1< ViewPresetListManagerCAP >  ViewPresetListManagerCAPs;

} //standalone
} //application

#endif //INCLUDED_STANDALONE_APPLICATION_VIEWPRESETLISTMANAGER_FWD_HH
