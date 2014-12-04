#include "stdafx.h"
#include "resource_loader.h"
#include "core/app.h"
#include "utils/utils.h"
#include "style/style_parser.h"
#include "dom/ui_parser.h"

namespace ui
{
	ResourceLoader* ResourceLoader::Get()
	{
		return App::Get()->GetResourceLoader();
	}

	ResourceLoader::ResourceLoader()
	{
		base_path_ = dirname(App::Get()->GetAppPath());
	}

	ResourceLoader::~ResourceLoader()
	{

	}

	void ResourceLoader::Rebase(const std::wstring& path)
	{
		assert(isdir(path));
		base_path_ = path;
	}

	std::wstring ResourceLoader::ResolvePath(const std::wstring& relative) const
	{
		return pathcombine(base_path_, relative);
	}

	bool ResourceLoader::LoadFileToString(const std::wstring& relative, std::string* contnets)
	{
		return ReadFileToString(ResolvePath(relative), contnets);
	}

	bool ResourceLoader::LoadFileToString(const URL& url, std::string* contents)
	{
		if (!url.is_valid() || url.is_empty())
			return false;

		std::wstring real_path;
		if (url.SchemeIs("res")) {
			real_path = pathcombine(base_path_, MultiByteToWide(url.path()));
		}
		else if (url.SchemeIs("file")) {
			real_path = MultiByteToWide(url.path());
		}
		else {
			return false;//������֧��
		}

		if (!LoadFileToString(real_path, contents))
			return false;
		return true;
	}

	scoped_refptr<StyleSheet> ResourceLoader::GetStyleSheet(const ResourceId& id)
	{
		return GetStyleSheet(ResolveId(id));
	}

	scoped_refptr<StyleSheet> ResourceLoader::GetStyleSheet(const URL& url)
	{
		std::string contents;
		if (!LoadFileToString(url, &contents))
			return NULL;

		StyleParser parser;
		scoped_refptr<StyleSheet> sheet(new StyleSheet(url));
		parser.SetStyleSheet(sheet.get());
		if (!parser.ParseSheet(contents, 0))
			return NULL;
		return sheet;
	}

	ui::UIDocumentPtr ResourceLoader::GetUIDocument(const ResourceId& id)
	{
		return GetUIDocument(ResolveId(id));
	}

	ui::UIDocumentPtr ResourceLoader::GetUIDocument(const URL& url)
	{
		std::string contents;
		if (!LoadFileToString(url, &contents))
			return NULL;

		UIParser parser;
		UIDocumentPtr document(new UIDocument(url));
		parser.SetDomDocument(document);
		if (!parser.ParseXmlDocument(contents))
			return NULL;
		return document;
	}

	URL ResourceLoader::ResolveId(const ResourceId& id)
	{
		//TODO: ʵ��
		assert(0);
		return URL();
	}

}