#pragma once

#include "rect.h"

class Normal
{
public:
	Normal(void);
	~Normal(void);

	virtual Rect border() const = 0; // boundingRect, �����Rect���Զ�������(��������ϵ), ����qt���Ǹ�QRect
	virtual void norm(qreal maxL, QPointF center)=0; // �����ֱ�����߿�����ĵ�

};

