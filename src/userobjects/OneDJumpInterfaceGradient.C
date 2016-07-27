#include "OneDJumpInterfaceGradient.h"

template<>
InputParameters validParams<OneDJumpInterfaceGradient>()
{
  InputParameters params = validParams<InternalSideUserObject>();
  params.addRequiredCoupledVar("variable", "the variable name this userobject is acting on.");
  params.addRequiredParam<std::string>("jump", "the name of the variable that will store the jump");

  return params;
}

OneDJumpInterfaceGradient::OneDJumpInterfaceGradient(const InputParameters & parameters) :
    InternalSideUserObject(parameters),
    _aux(_fe_problem.getAuxiliarySystem()),
    _grad_u(coupledGradient("variable")),
    _grad_u_neighbor(coupledNeighborGradient("variable")),
    _jump_name(getParam<std::string>("jump")),
    _value(0.)
{
}

OneDJumpInterfaceGradient::~OneDJumpInterfaceGradient()
{
}

void
OneDJumpInterfaceGradient::initialize()
{
  NumericVector<Number> & sln = _aux.solution();
  _aux.system().zero_variable(sln, _aux.getVariable(_tid, _jump_name).number());
  sln.close();
}

void
OneDJumpInterfaceGradient::execute()
{
  dof_id_type dof_nb_aux = _current_elem->n_dofs(_aux.number(), _fe_problem.getVariable(_tid, _jump_name).number());
  dof_id_type dof_nb = 0.;
  dof_id_type dof_nb_neighbor = 0.;

  if (dof_nb_aux != 0)
  {
    _value = 0.;
    NumericVector<Number> & sln = _aux.solution();

    // Compute the jump of the given variable:(grad(f_i)_x - grad(f_ip1)_x)
    for (unsigned int qp = 0; qp < _q_point.size(); ++qp)
      _value = std::max(std::fabs(_grad_u[qp](0) - _grad_u_neighbor[qp](0)), _value);

    dof_nb = _current_elem->dof_number(_aux.number(), _fe_problem.getVariable(_tid, _jump_name).number(), 0);
    dof_nb_neighbor = _neighbor_elem->dof_number(_aux.number(), _fe_problem.getVariable(_tid, _jump_name).number(), 0);

    if (_current_elem->on_boundary())
    {
      sln.add(dof_nb, _value);
      sln.add(dof_nb_neighbor, _value);
    }
    else if (_neighbor_elem->on_boundary())
    {
      sln.add(dof_nb, _value);
      sln.add(dof_nb_neighbor, _value);
    }
    else
    {
      sln.add(dof_nb, _value);
      sln.add(dof_nb_neighbor, _value);
    }
  }
}

void
OneDJumpInterfaceGradient::destroy()
{
}

void
OneDJumpInterfaceGradient::finalize()
{
  _aux.solution().close();
}

void
OneDJumpInterfaceGradient::threadJoin(const UserObject & /*uo*/)
{
}
