#pragma once
namespace Tools{
	enum Number
	{
		zero,
		one,
		two,
		three,
		four ,
		five,
		six ,
		seven
	};
	enum Menu
	{
		One,
		Two,
		Three,
		Four,
		Five,
		Max
	};
	enum content{
		next,
		group,
		custom,
		current,
		distinct,
		previous,
	};
	enum columns{
		id = 0,
		pointx = 4,
		pointy = 5,
		pointz = 2,
		radius = 3,
		objectz = 1,
		IsPoint = 6,
		maxcolumns
	};
	enum keyboard{
		noKey,
		EscKey,
		EnterKey,
		LshiftKey,
		RshiftKey,
		controlKey,
		upArrowKey,
		alternateKey,
		leftArrowKey,
		downArrowKey,
		rightArrowKey,
		relevateKeys,
	};
}

