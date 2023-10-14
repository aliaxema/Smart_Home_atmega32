

#include "../BIT_MATH.h"
#include "../STD_TYPES.h"


#include "EEPROM_interface.h"
#include "../I2C/TWI_interface.h"

void EEPROM_voidInit(void)
{
	TWI_voidInitMaster(255);
}


void EEPROM_voidWriteByte(u16 Copy_u16WordAddress, u8 Copy_u8Data)
{
	u8 local_u8Address = (Copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_voidSendStartCondition();
	
	// Send slave address with write operation
	TWI_voidSendSlaveAddWithWrite(local_u8Address);
	
	// Send word address
	TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress);
	
	// Send byte data
	TWI_voidSendMasterDataByte(Copy_u8Data);
	
	// Send stop condition
	TWI_voidSendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);
	
}


void EEPROM_voidReadByte(u16 Copy_u16WordAddress, u8* Copy_pu8RxData)
{
	if(Copy_pu8RxData != NULL)
	{
	    u8 local_u8Address = (Copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;
	    
	    // Send start condition
	    TWI_voidSendStartCondition();
	    
	    // Send slave address with write operation
	    TWI_voidSendSlaveAddWithWrite(local_u8Address);
	    
	    // Send word address
	    TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress);
	    
	    // Send Repeated start condition
	    TWI_voidSendRepStartCondition();
	    
	    // Send slave address with read operation
	    TWI_voidSendSlaveAddWithRead(local_u8Address);
	    
	    // Read byte data
	    TWI_voidRecieveMasterDataByte(Copy_pu8RxData);
	    
	    // Send stop condition
	    TWI_voidSendStopCondition();
	    
	    // Self-timed Cycle delay
	    _delay_ms(5);
		
		
	}
}


void EEPROM_voidWritePage(u16 Copy_u16WordAddress, u8* data_arr, u8 arr_size)
{
	u8 i, local_u8Address = (Copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_voidSendStartCondition();
	
	// Send slave address with write operation
	TWI_voidSendSlaveAddWithWrite(local_u8Address);
	
	// Send word address
	TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress);
	
	for (i=0;i<arr_size;i++)
	{
		// Send byte data
		TWI_voidSendMasterDataByte(data_arr[i]);			
	}
	// Send stop condition
	TWI_voidSendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);	
}

void EEPROM_voidReadPage(u16 Copy_u16WordAddress, u8* data_arr, u8 arr_size)
{
	
	if(data_arr != NULL)
	{
		u8 i,new_size=0, local_u8Address = (Copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;
		
		// Send start condition
		TWI_voidSendStartCondition();
		
		// Send slave address with write operation
		TWI_voidSendSlaveAddWithWrite(local_u8Address);
		
		// Send word address
		TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress);
		
		// Send Repeated start condition
		TWI_voidSendRepStartCondition();
		
		// Send slave address with read operation
		TWI_voidSendSlaveAddWithRead(local_u8Address);
		
		//making sure the addres is less than or equal to 16
		new_size = arr_size >= 16 ? 16 : arr_size ;
		
		for (i=0;i<new_size;i++)
		{
			// Read Page data
			TWI_voidRecieveMasterDataByte(data_arr);
			data_arr++;
		}
		// Send stop condition
		TWI_voidSendStopCondition();
		
		// Self-timed Cycle delay
		_delay_ms(5);
		//SET_BIT(PORTA,5);
	}
}
