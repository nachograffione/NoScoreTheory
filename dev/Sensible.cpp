#include "Sensible.h"

Sensible::Sensible() : m_isSensible(true){
}


void Sensible::switchSensible(){
	setSensible(!m_isSensible);
}


void Sensible::setSensible(bool isSensible){
	m_isSensible = isSensible;
}


bool Sensible::getSensible(){
	return m_isSensible;
}
