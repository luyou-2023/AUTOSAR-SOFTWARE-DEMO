

/* Add RTE Application header */
#include "Rte_TemControlSWC.h"

//数据流动顺序为 SWC -> RTE -> ECU 抽象层 -> MCAL
/**
最终的代码是在 ECU（电子控制单元）上运行的。以下是对这一过程的总结：

SWC（软件组件）：

包含实现特定功能的代码，例如控制逻辑或数据处理。SWC 是应用层的核心部分。
RTE（运行时环境）：

作为 SWC 和基础软件之间的桥梁，负责数据的传输和事件的处理，使得不同 SWC 能够相互通信而不依赖于底层实现。
ECU 抽象层：

为上层软件提供硬件抽象，简化了与具体硬件的交互。上层软件不需要了解硬件细节，从而提高了移植性。
MCAL（微控制器抽象层）：

直接与微控制器的硬件交互，提供硬件外设的驱动接口，确保上层应用可以通过标准接口访问硬件功能。
最终代码在 ECU 上运行
所有的代码最终都会被编译并上传到 ECU 上运行，具体的执行过程是：

SWC 中的逻辑代码通过 RTE 进行调用和通信。
RTE 管理着与 ECU 抽象层 的交互，确保代码与硬件的解耦。
MCAL 提供具体的硬件操作接口，直接与微控制器硬件交互。
这种分层架构使得开发过程更加模块化和灵活，同时也为后续的维护和更新提供了便利。
**/
void ApplTemperatureControl()
{
	
	float Temperature;
	
	/* Read data from Ecu Abstraction through RTE */
	Rte_Read_RP_Temperature_Temperature(&Temperature);
	
	/* Control Logic */
	if(Temperature > 50 && Temperature < 75)
	{
		/* Start Cooling fan (LowSpeed) */
		Rte_Call_RP_StartMotor_StartMotor(25);
	}
	else if(Temperature > 75)
	{
		/* start cooling fan (HighSpeed) */
		Rte_Call_RP_StartMotor_StartMotor(100);
	}
	else if(Temperature < 50)
	{
		/* Stop the cooling fan */
		Rte_Call_RP_StopMotor_StopMotor();
	}
	
	
}