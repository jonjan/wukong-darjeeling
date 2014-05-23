/*
 * opcodes.c
 * 
 * Copyright (c) 2008-2010 CSIRO, Delft University of Technology.
 * 
 * This file is part of Darjeeling.
 * 
 * Darjeeling is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Darjeeling is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with Darjeeling.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(DARJEELING_DEBUG) && defined(DARJEELING_DEBUG_TRACE)

const char *jvm_opcodes[] = {
"nop",
"sconst_m1",
"sconst_0",
"sconst_1",
"sconst_2",
"sconst_3",
"sconst_4",
"sconst_5",
"iconst_m1",
"iconst_0",
"iconst_1",
"iconst_2",
"iconst_3",
"iconst_4",
"iconst_5",
"aconst_null",
"bspush",
"bipush",
"sspush",
"sipush",
"iipush",
"lds",
"sload",
"sload_0",
"sload_1",
"sload_2",
"sload_3",
"iload",
"iload_0",
"iload_1",
"iload_2",
"iload_3",
"aload",
"aload_0",
"aload_1",
"aload_2",
"aload_3",
"sstore",
"sstore_0",
"sstore_1",
"sstore_2",
"sstore_3",
"istore",
"istore_0",
"istore_1",
"istore_2",
"istore_3",
"astore",
"astore_0",
"astore_1",
"astore_2",
"astore_3",
"baload",
"caload",
"saload",
"iaload",
"aaload",
"bastore",
"castore",
"sastore",
"iastore",
"aastore",
"ipop",
"ipop2",
"idup",
"idup2",
"idup_x1",
"iswap_x",
"apop",
"apop2",
"adup",
"adup2",
"adup_x1",
"adup_x2",
"aswap",
"getfield_b",
"getfield_c",
"getfield_s",
"getfield_i",
"getfield_a",
"putfield_b",
"putfield_c",
"putfield_s",
"putfield_i",
"putfield_a",
"getstatic_b",
"getstatic_c",
"getstatic_s",
"getstatic_i",
"getstatic_a",
"putstatic_b",
"putstatic_c",
"putstatic_s",
"putstatic_i",
"putstatic_a",
"sadd",
"ssub",
"smul",
"sdiv",
"srem",
"sneg",
"sshl",
"sshr",
"sushr",
"sand",
"sor",
"sxor",
"iadd",
"isub",
"imul",
"idiv",
"irem",
"ineg",
"ishl",
"ishr",
"iushr",
"iand",
"ior",
"ixor",
"binc",
"sinc",
"iinc",
"s2b",
"s2i",
"i2b",
"i2s",
"ifeq",
"ifne",
"iflt",
"ifge",
"ifgt",
"ifle",
"ifnull",
"ifnonnull",
"if_scmpeq",
"if_scmpne",
"if_scmplt",
"if_scmpge",
"if_scmpgt",
"if_scmple",
"if_icmpeq",
"if_icmpne",
"if_icmplt",
"if_icmpge",
"if_icmpgt",
"if_icmple",
"if_acmpeq",
"if_acmpne",
"goto",
"goto_w",
"tableswitch",
"lookupswitch",
"sreturn",
"ireturn",
"areturn",
"return",
"invokevirtual",
"invokespecial",
"invokestatic",
"invokeinterface",
"new",
"newarray",
"anewarray",
"arraylength",
"athrow",
"checkcast",
"instanceof",
"monitorenter",
"monitorexit",
"idup_x2",
"iinc_w",
"sinc_w",
"i2c",
"s2c",
"b2c",
"idup_x",
"sifeq",
"sifne",
"siflt",
"sifge",
"sifgt",
"sifle",
"lconst_0",
"lconst_1",
"lload",
"lload_0",
"lload_1",
"lload_2",
"lload_3",
"llpush",
"lstore",
"lstore_0",
"lstore_1",
"lstore_2",
"lstore_3",
"laload",
"lastore",
"getfield_l",
"putfield_l",
"getstatic_l",
"putstatic_l",
"ladd",
"lsub",
"lmul",
"ldiv",
"lrem",
"lneg",
"lshl",
"lshr",
"lushr",
"land",
"lor",
"lxor",
"lreturn",
"l2i",
"l2s",
"i2l",
"s2l",
"lcmp"
};
#endif // defined(DARJEELING_DEBUG) && defined(DARJEELING_DEBUG_TRACE)
