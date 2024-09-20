

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

/**
开发特定的汽车电子功能时，通常遵循以下步骤：

功能定义：

首先明确要实现的汽车电子功能，例如温度控制、动力转向等。
MCAL 实现：

根据所选微控制器（MCU）的特性，开发 MCAL 层，提供与硬件外设的交互接口。这包括 GPIO、ADC、PWM 等驱动程序。
ECU 抽象层功能实现：

实现 ECU 抽象层的功能，使得上层软件不需要关心具体的硬件细节。将硬件抽象接口注册到 RTE，以便上层 SWC 可以使用。
RTE 注册：

在 RTE 中配置和注册 ECU 抽象层和 MCAL 接口，以实现 SWC 与基础软件的通信。
SWC 开发：

最后，开发 SWC 的具体处理逻辑。这包括数据处理、控制算法、状态机等逻辑，实现应用的核心功能。
整个流程的关键点：
各层之间的清晰分工，使得开发过程更加模块化。
通过 RTE 进行解耦，允许开发人员在不依赖于底层硬件的情况下专注于应用逻辑。
每一层的实现可以独立更新和维护，提升了系统的灵活性和可扩展性。
通过这样的方式，您可以有效地开发和维护汽车电子功能，确保系统的稳定性和性能。
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