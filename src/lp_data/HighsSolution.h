/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2020 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file lp_data/HighsSolution.h
 * @brief Class-independent utilities for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef LP_DATA_HIGHSSOLUTION_H_
#define LP_DATA_HIGHSSOLUTION_H_

#include <string>
#include <vector>

#include "lp_data/HighsInfo.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsStatus.h"

class HighsLp;
struct IpxSolution;
class HighsOptions;
class HighsModelObject;

using std::string;

struct HighsPrimalDualErrors {
  int num_nonzero_basic_duals;
  int num_large_nonzero_basic_duals;
  double max_nonzero_basic_dual;
  double sum_nonzero_basic_duals;
  int num_off_bound_nonbasic;
  double max_off_bound_nonbasic;
  double sum_off_bound_nonbasic;
  int num_primal_residual;
  double max_primal_residual;
  double sum_primal_residual;
  int num_dual_residual;
  double max_dual_residual;
  double sum_dual_residual;
};

void getPrimalDualInfeasibilities(
    const HighsLp& lp, const HighsBasis& basis, const HighsSolution& solution,
    HighsSolutionParams& solution_params);

void analyseVarBasicSolution(const double primal_feasibility_tolerance,
                             const double dual_feasibility_tolerance,
                             const HighsBasisStatus status, const double lower,
                             const double upper, const double value,
                             const double dual, 
                             double& primal_infeasibility,
                             double& dual_infeasibility);

#ifdef HiGHSDEV
void analyseSimplexAndHighsSolutionDifferences(
    const HighsModelObject& highs_model_object);
#endif

#ifdef IPX_ON
HighsStatus ipxSolutionToHighsSolution(
    FILE* logfile, const HighsLp& lp, const std::vector<double>& rhs,
    const std::vector<char>& constraint_type, const int ipx_num_col,
    const int ipx_num_row, const std::vector<double>& ipx_x,
    const std::vector<double>& ipx_slack_vars,
    // const std::vector<double>& ipx_y,
    HighsSolution& highs_solution);
HighsStatus ipxBasicSolutionToHighsBasicSolution(
    FILE* logfile, const HighsLp& lp, const std::vector<double>& rhs,
    const std::vector<char>& constraint_type, const IpxSolution& ipx_solution,
    HighsBasis& highs_basis, HighsSolution& highs_solution);
#endif

std::string iterationsToString(const HighsIterationCounts& iterations_counts);

void resetModelStatusAndSolutionParams(HighsModelObject& highs_model_object);
void resetModelStatusAndSolutionParams(HighsModelStatus& model_status,
                                       HighsSolutionParams& solution_params,
                                       const HighsOptions& options);
void resetSolutionParams(HighsSolutionParams& solution_params,
                         const HighsOptions& options);

void invalidateSolutionParams(HighsSolutionParams& solution_params);
void invalidateSolutionStatusParams(HighsSolutionParams& solution_params);
void invalidateSolutionInfeasibilityParams(
    HighsSolutionParams& solution_params);

void copySolutionObjectiveParams(
    const HighsSolutionParams& from_solution_params,
    HighsSolutionParams& to_solution_params);

void copyFromSolutionParams(HighsInfo& highs_info,
                            const HighsSolutionParams& solution_params);

#endif  // LP_DATA_HIGHSSOLUTION_H_
