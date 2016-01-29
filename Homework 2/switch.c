int switch_prob(int x, int n)
{ 
    int result = x;

    switch(n) {
	case 50:
	case 52:
		result = result << 2;
		break;
	case 53:
		result = result >> 2;
		break;
	case 54:
		result = result * 3;
	case 55:
		result = result * result;
	case 51:
	default:
		result = result + 10;
		break;
    } 

    return result;
}

//x -> eax
//n -> edx
//n = n - 50;
//if edx > 5, goto switch_prob + 0x28
//otherwise jump switch table