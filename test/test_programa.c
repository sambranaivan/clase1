#include "unity.h"
#include "programa.h"

void setUp(void)
{
	
}

void tearDown(void)
{

}

//Para enviar un evento al modulo se llama al manejador de eventos del mismo con el evento como argumento.
void test_FrameworkOk	( void )
{
	TEST_ASSERT_EQUAL(1,1);
}