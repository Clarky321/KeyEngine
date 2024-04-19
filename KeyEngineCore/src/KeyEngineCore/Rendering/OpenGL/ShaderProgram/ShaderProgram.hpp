// ������ �� �������������� ��������� ������������� �����
#pragma once

namespace KeyEngine {

	class ShaderProgram
	{
	public:
		// ����������� ������ ShaderProgram, ����������� �������� ���� ���������� � ������������ ��������
		ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);

		// ����������� �����������
		ShaderProgram(ShaderProgram&&);

		// �������� �����������
		ShaderProgram& operator=(ShaderProgram&&);

		// ���������� ������ ShaderProgram
		~ShaderProgram();

		// ��������� �������� �������� �� ���������, ����������� � ������������
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		// ����� ��� �������� ��������� ���������
		void bind() const;

		// ����������� ����� ��� ������� ��������� ���������
		static void unbind();

		// ����� ��� ��������, ���� �� ��������� ������� ��������������
		bool isCompiled() const { return m_isCompiled; }

	private:
		// ���������� ��� �������� ���������� � ���, ���� �� ��������� ��������������
		bool m_isCompiled = false;

		// ������������� ��������� ���������
		unsigned int m_id = 0;
	};
}