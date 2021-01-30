#include "LabelManager.h"

#include "../Errors/Errors.h"

unordered_map<string, LabelData> LabelManager::m_labels;

bool LabelManager::isLabelExist(const string & name) {
	return (m_labels.find(name) != m_labels.end());
}

void LabelManager::addLabel(const string &name, const LabelData &data) {
	if (!LabelManager::isLabelExist(name)) {
		m_labels.insert(make_pair(name, data));
	} else {
		throw LabelRedefinition;
	}
}

void LabelManager::setAbsoluteLabelValue(const string &name, const int &value) {
	auto it = m_labels.find(name);
	if (it != m_labels.end()) {
		it->second.value = value;
		it->second.isCounted = true;
	} else {
		throw UndefinedAbsoluteLabel;
	}
}

LabelData LabelManager::getLabelData(const string &name) {
	auto it = m_labels.find(name);
	if (it != m_labels.end()) {
		return it->second;
	} else {
		throw UndefinedLabel;
	}
}

int LabelManager::getLabelValue(const string &name) {
	auto iter = m_labels.find(name);
	if (iter != m_labels.end())
		if (iter->second.isCounted)
			return iter->second.value;
		else
			throw UndefinedAbsoluteLabel;
	else
		throw UndefinedLabel;
}
