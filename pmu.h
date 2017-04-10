//The head file of PMU module

#ifndef ENTRY
#define ENTRY(name) \
	.globl name; \
	.align 4;\
name:
#endif

#ifndef ENDPROC
#define ENDPROC(name) \
	.type name, @function; \
	.size name, .-name
#endif

//ENTRY(pmu_setup)
void pmu_setup(void)
{
	asm volatile(
		"MRS	x0, PMCR_EL0\n"
		"LDR	x1, =0x47\n"
		"ORR	x0, x1, x0\n"
		"MSR	PMCR_EL0, x0\n"
		
		"MRS	x0, PMCR_EL0\n"
		"bic	x0, x0, #(1<<5)\n"
		"MSR	PMCR_EL0, x0\n"
/*		
		"MRS	x0, mdcr_e13\n"
		"ORR	x0, x0, #(1<<17)\n"
		"MSR	mdcr_e13, x0\n"
*/		
		"LDR	x2, =0x800000ff\n"
		"MSR	PMCNTENSET_EL0, x2\n"
		
		"isb sy\n"
//		"RET\n"
	);
}
//ENDPROC(pmu_setup)

inline unsigned long pmu_get_cycle(void)
{
	unsigned long value;

	asm volatile(
		"MRS	%0,	PMCCNTR_EL0\n"
		:"=&r"(value)
	);
	return value;
}
