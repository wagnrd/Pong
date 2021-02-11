/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   G O L D E N   S E C T I O N   O R D E R   C L A S S   H E A D E R                                          */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artificial Intelligence Techniques SL                                                                      */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __GOLDENSECTIONORDER_H__
#define __GOLDENSECTIONORDER_H__

// System includes

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "training_strategy.h"

#include "order_selection_algorithm.h"

// TinyXml includes

#include "tinyxml2.h"

namespace OpenNN
{

///
/// This concrete class represents a golden section algorithm for the order selection of a neural network.
///

class GoldenSectionOrder : public OrderSelectionAlgorithm
{
public:
    // DEFAULT CONSTRUCTOR

    explicit GoldenSectionOrder();

    // TRAINING STRATEGY CONSTRUCTOR

    explicit GoldenSectionOrder(TrainingStrategy*);

    // XML CONSTRUCTOR

    explicit GoldenSectionOrder(const tinyxml2::XMLDocument&);

    // FILE CONSTRUCTOR

    explicit GoldenSectionOrder(const string&);

    // DESTRUCTOR

    virtual ~GoldenSectionOrder();


    // STRUCTURES

    ///
    /// This structure contains the training results for the golden section order method.
    ///

    struct GoldenSectionOrderResults : public OrderSelectionAlgorithm::OrderSelectionResults
    {
        /// Default constructor.

        explicit GoldenSectionOrderResults() : OrderSelectionAlgorithm::OrderSelectionResults()
        {
        }

        /// Destructor.

        virtual ~GoldenSectionOrderResults()
        {
        }

    };

    // Order selection methods

    GoldenSectionOrderResults* perform_order_selection();

    // Serialization methods

    tinyxml2::XMLDocument* to_XML() const;
    void from_XML(const tinyxml2::XMLDocument&);

    void write_XML(tinyxml2::XMLPrinter&) const;
    // void read_XML(   );

    void save(const string&) const;
    void load(const string&);


};

}

#endif

// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2018 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
