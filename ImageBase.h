#ifndef IMAGE_BASE_H
#define IMAGE_BASE_H

#include <iostream>
#include <fstream>
#include <vector>

//#include "image_pgm_ppm.h"

typedef unsigned char OCTET;

class ImageBase {

public:

	ImageBase();
	ImageBase(size_t width, size_t height);
	ImageBase(const std::string& filename);

	size_t height() const;
	size_t width() const;
	size_t size() const;

	bool valid() const;
	bool on_bounds(size_t raw, size_t column) const;
	bool same_resolution(const ImageBase& image) const;

	void load(const std::string& filename);
	void save(const std::string& filename);

protected:

	size_t m_height;
	size_t m_width;
	bool m_valid;

	// charge une image en fonction de sont type (.ppm / .pgm)
	virtual void load(std::istream& is) = 0;
	virtual void save(std::ostream& os) const = 0;
};

////////////////////////////////// ImagePGM ////////////////////////////////////////

class ImagePGM : public ImageBase {

public:

	using ImageBase::load;
	using ImageBase::save;

	typedef OCTET* iterator;
    typedef const OCTET* const_iterator;

	ImagePGM() : ImageBase(), m_data() {}
	ImagePGM(size_t width, size_t height) : ImageBase(width, height), m_data(height * width) {}
	ImagePGM(size_t width, size_t height, bool fill);
	ImagePGM(const std::string& filename) : ImageBase(filename), m_data() {}

	void resize(size_t width, size_t height);

	// Access data in array style pgm(n)
	OCTET& operator[](size_t n);
	const OCTET& operator[](size_t n) const;

	// Access data in matrix style pgm(i, j)
	OCTET& operator()(size_t raw, size_t column);
	const OCTET& operator()(size_t raw, size_t column) const;

	// Accessor of internal data
	OCTET* data();
	const OCTET* data() const;

	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

protected:

	std::vector<OCTET> m_data;

	void load(std::istream& is);
	void save(std::ostream& os) const;
};

////////////////////////////////// ImagePNG ////////////////////////////////////////

class ImagePNG : public ImageBase {

public:

	using ImageBase::ImageBase;

	ImagePNG(size_t width, size_t height) : ImageBase(width, height), m_red(width, height), m_green(width, height), m_blue(width, height), m_alpha(width, height, true)  {}
	ImagePNG(const std::string& filename) : ImageBase(filename), m_red(), m_green(), m_blue(), m_alpha()  {}

	ImagePNG(const ImagePGM& red, const ImagePGM& green, const ImagePGM& blue, const ImagePGM& alpha);

	size_t size() const;

	// Access data in array style pgm(n)
	OCTET& operator[](size_t n);
	const OCTET& operator[](size_t n) const;

	// Access data in matrix style pgm(i, j)
	OCTET& operator()(size_t raw, size_t column, size_t channel);
	const OCTET& operator()(size_t raw, size_t column, size_t channel) const;


	OCTET& red(size_t raw, size_t column);
	const OCTET& red(size_t raw, size_t column) const;

	OCTET& green(size_t raw, size_t column);
	const OCTET& green(size_t raw, size_t column) const;

	OCTET& blue(size_t raw, size_t column);
	const OCTET& blue(size_t raw, size_t column) const;

	OCTET& alpha(size_t raw, size_t column);
	const OCTET& alpha(size_t raw, size_t column) const;

	// Getters/Setters pour checker que les resolutions des parties R/G/B/A de l'image sont les mêmes.

	const ImagePGM& red() const;
	const ImagePGM& green() const;
	const ImagePGM& blue() const;
	const ImagePGM& alpha() const;

	void red(const ImagePGM& red);
	void green(const ImagePGM& green);
	void blue(const ImagePGM& blue);
	void alpha(const ImagePGM& alpha);
	void load(const std::string& filename);
	void save(const std::string& filename) const;

protected:

	ImagePGM m_red;
	ImagePGM m_green;
	ImagePGM m_blue;
	ImagePGM m_alpha;


	void load(std::istream& is);
	void save(std::ostream& os) const;
};

#endif