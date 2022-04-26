#ifndef SENSIBLE_H
#define SENSIBLE_H

class Sensible {
protected:
	bool m_isSensible;
	
public:
	Sensible();
	bool getSensible();
	void setSensible(bool isSensible);
	void switchSensible();
};

#endif

