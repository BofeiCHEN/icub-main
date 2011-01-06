// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <iCub/DebugInterfaces.h>
//A collection of debug methods useful to send raw commands directly to the control boards.

bool yarp::dev::ImplementDebugInterface::setParameter(int j, unsigned int type, double value)
{
	int k=castToMapper2(helper)->toHw(j);
	return raw->setParameterRaw(j, type, value);
}

bool yarp::dev::ImplementDebugInterface::getParameter(int j, unsigned int type, double* value)
{
	int k=castToMapper2(helper)->toHw(j);
    return raw->getParameterRaw(j, type, value);
}

bool yarp::dev::ImplementDebugInterface::setDebugParameter(int j, unsigned int index, double value)
{
	int k=castToMapper2(helper)->toHw(j);
	return raw->setDebugParameterRaw(j, index, value);
}

bool yarp::dev::ImplementDebugInterface::getDebugParameter(int j, unsigned int index, double* value)
{
	int k=castToMapper2(helper)->toHw(j);
    return raw->getDebugParameterRaw(j, index, value);
}

yarp::dev::ImplementDebugInterface::ImplementDebugInterface(IDebugInterfaceRaw *r)
{
    raw=r;
    helper=0;
}

bool yarp::dev::ImplementDebugInterface::initialize(int size, const int *amap)
{
    if (helper!=0)
        return false;
    
    double *dummy=new double [size];
    for(int k=0;k<size;k++)
        dummy[k]=0;

    helper=(void *)(new ControlBoardHelper2(size, amap, dummy, dummy, dummy));
    _YARP_ASSERT_DEBUG(helper != 0);

    delete [] dummy;
    return true;
}

yarp::dev::ImplementDebugInterface::~ImplementDebugInterface()
{
    uninitialize();
}

bool yarp::dev::ImplementDebugInterface::uninitialize ()
{
    if (helper!=0)
    {
        delete castToMapper2(helper);
        helper=0;
    }
 
    return true;
}

