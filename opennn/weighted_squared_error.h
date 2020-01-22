//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   W E I G H T E D   S Q U A R E D   E R R O R    C L A S S   H E A D E R
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef WEIGHTEDSQUAREDERROR_H
#define WEIGHTEDSQUAREDERROR_H

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>

// OpenNN includes

#include "config.h"
#include "loss_index.h"
#include "data_set.h"
#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the weighted squared error term.

///
/// The weighted squared error measures the difference between the outputs from a neural network and the targets in a data set.
/// This functional is used in data modeling problems, such as function regression, 
/// classification and time series prediction.

class WeightedSquaredError : public LossIndex
{

public:

   // DEFAULT CONSTRUCTOR

   explicit WeightedSquaredError();

   // NEURAL NETWORK CONSTRUCTOR

   explicit WeightedSquaredError(NeuralNetwork*);

   // DATA SET CONSTRUCTOR

   explicit WeightedSquaredError(DataSet*);

   // DATA SET & NEURAL NETWORK CONSTRUCTOR
   explicit WeightedSquaredError(NeuralNetwork*, DataSet*);

   // XML CONSTRUCTOR

   explicit WeightedSquaredError(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   WeightedSquaredError(const WeightedSquaredError&);

   virtual ~WeightedSquaredError(); 

   // Get methods

   double get_positives_weight() const;
   double get_negatives_weight() const;

   double get_training_normalization_coefficient() const;
   double get_selection_normalization_coefficient() const;

   // Set methods

   // Error methods

   void set_default();

   void set_positives_weight(const double&);
   void set_negatives_weight(const double&);

   void set_training_normalization_coefficient(const double&);
   void set_selection_normalization_coefficient(const double&);

   void set_weights(const double&, const double&);

   void set_weights();

   void set_training_normalization_coefficient();
   void set_selection_normalization_coefficient();

   double calculate_batch_error(const VectorXi&) const;
   double calculate_batch_error(const VectorXi&, const Tensor<type, 1>&) const;

   Tensor<type, 1> calculate_training_error_gradient() const;

   LossIndex::FirstOrderLoss calculate_first_order_loss() const;
   LossIndex::FirstOrderLoss calculate_first_order_loss(const DataSet::Batch&) const;

   void calculate_first_order_loss(const DataSet::Batch&, const NeuralNetwork::ForwardPropagation&, FirstOrderLoss&) const
   {

   }

   Tensor<type, 2> calculate_output_gradient(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   void calculate_output_gradient(const DataSet::Batch& batch,
                                  const NeuralNetwork::ForwardPropagation& forward_propagation,
                                  FirstOrderLoss& first_order_loss) const
   {
        #ifdef __OPENNN_DEBUG__

        check();

        #endif

        const int trainable_layers_number = neural_network_pointer->get_trainable_layers_number();

        first_order_loss.output_gradient = (forward_propagation.layers[trainable_layers_number-1].activations-batch.targets_2d)
                *((batch.targets_2d-static_cast<type>(1.0))*(static_cast<type>(-1.0))*negatives_weight + batch.targets_2d*positives_weight);
   }


   // Error terms methods

   Tensor<type, 1> calculate_training_error_terms(const Tensor<type, 1>&) const;
   Tensor<type, 1> calculate_training_error_terms(const Tensor<type, 2>&, const Tensor<type, 2>&) const;

   LossIndex::SecondOrderLoss calculate_terms_second_order_loss() const;

   string get_error_type() const;
   string get_error_type_text() const;

   // Serialization methods

   tinyxml2::XMLDocument* to_XML() const;   
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;

   string object_to_string() const;

private:

   /// Weight for the positives for the calculation of the error.

   type positives_weight;

   /// Weight for the negatives for the calculation of the error.

   type negatives_weight;

   /// Coefficient of normalization for the calculation of the training error.

   type training_normalization_coefficient;

   /// Coefficient of normalization for the calculation of the selection error.

   type selection_normalization_coefficient;
};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
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
