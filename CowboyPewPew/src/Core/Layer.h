#pragma once

class Layer
{
public:

	Layer() = default;

	virtual void OnBegin() = 0;

	virtual void OnUpdate(Timestep delta) = 0;

	virtual void OnRemove() = 0;

private:

};
