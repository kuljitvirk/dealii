// ---------------------------------------------------------------------
//
// Copyright (C) 2016 - 2018 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------



#include <deal.II/base/config.h>

#include <deal.II/fe/fe_series.h>

#include <iostream>


DEAL_II_NAMESPACE_OPEN

namespace FESeries
{
  std::pair<double, double>
  linear_regression(const std::vector<double> &x, const std::vector<double> &y)
  {
    FullMatrix<double> K(2, 2), invK(2, 2);
    Vector<double>     X(2), B(2);

    Assert(x.size() == y.size(),
           ExcMessage("x and y are expected to have the same size"));

    Assert(x.size() >= 2,
           dealii::ExcMessage(
             "at least two points are required for linear regression fit"));

    double sum_1 = 0.0, sum_x = 0.0, sum_x2 = 0.0, sum_y = 0.0, sum_xy = 0.0;

    for (unsigned int i = 0; i < x.size(); ++i)
      {
        sum_1 += 1.0;
        sum_x += x[i];
        sum_x2 += x[i] * x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
      }

    K(0, 0) = sum_1;
    K(0, 1) = sum_x;
    K(1, 0) = sum_x;
    K(1, 1) = sum_x2;

    B(0) = sum_y;
    B(1) = sum_xy;

    invK.invert(K);
    invK.vmult(X, B, false);

    return std::make_pair(X(1), X(0));
  }
} // namespace FESeries

DEAL_II_NAMESPACE_CLOSE
